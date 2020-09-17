// main package is the script which on running will setup a new
// daily problem directory and update readme using Github Actions
package main

import (
	"bytes"
	"errors"
	"fmt"
	"io/ioutil"
	"log"
	"os"
	"path"
	"strconv"
	"strings"
)

func main() {
	if os.Getenv("push") != "" {
		// runs using Github Actions' Push event
		// and update the readme
		onPush()
	}
	if os.Getenv("cron") != "" {
		// runs using Github Actions' Cron job every day
		// and setup a new problem directory
		onCronRun()
		onPush()
	}
}

func onPush() {
	fmt.Println("Updating the README")
	list, err := ioutil.ReadDir(".")
	if err != nil {
		log.Println("read dir error:", err)
		return
	}

	prob := make([]*ProblemData, 0, len(list))
	unsolved := make([]string, 0, len(list))

	for _, dir := range list {
		// check directory
		n, err := strconv.Atoi(dir.Name())
		if n == 0 || err != nil || !dir.IsDir() {
			continue
		}
		data := ""
		name := dir.Name()
		solList := make([]*SolutionData, 0, 2)

		solFiles, err := ioutil.ReadDir(dir.Name())
		if err != nil {
			log.Printf("read dir error for name(%v): %v\n", name, err)
			return
		}

		for _, file := range solFiles {
			fileN := file.Name()
			if len(fileN) < 5 || fileN[:5] != "code." || file.IsDir() {
				continue
			}
			filePath := path.Join(dir.Name(), fileN)
			if data == "" {
				data, err = extract(filePath)
				if err != nil {
					log.Printf("read file content error for name(%v): %v\n", name, err)
					data = ""
				}
			}
			ext := fileN[5:]
			switch ext {
			case "py":
				ext = "Python"
			case "cpp":
				ext = "C++"
			case "go":
				ext = "Golang"
			default:
				ext = strings.Title(ext)
			}
			solList = append(solList, &SolutionData{
				Language: ext,
				FilePath: filePath,
			})
		}

		if data == "\n\n\n" {
			unsolved = append(unsolved, name)
			continue
		}
		prob = append(prob, &ProblemData{
			Number:    name,
			Data:      data,
			Solutions: solList,
		})
	}
	if err := updateReadme(&Data{
		Problems: prob,
		Unsolved: unsolved,
	}); err != nil {
		log.Printf("error updating README: %v\n", err)
		return
	}
}

var (
	// ---------------------------
	stSep = bytes.Repeat([]byte("-"), 27)
	// Run Using
	// ---------
	endSep = []byte("Run Using\n---------")
)

func extract(file string) (string, error) {
	data, err := ioutil.ReadFile(file)
	if err != nil {
		return "", err
	}
	st := bytes.Index(data, stSep)
	if st == -1 {
		return "", errors.New("st not found")
	}
	st += len(stSep)
	en := bytes.Index(data, endSep)
	return string(data[st:en]), nil
}

func onCronRun() {
	fmt.Println("Setting up new Problem directory")
	list, err := ioutil.ReadDir(".")
	if err != nil {
		log.Println("read dir error:", err)
		return
	}
	last := 0
	for _, dir := range list {
		n, err := strconv.Atoi(dir.Name())
		if n == 0 || err != nil || !dir.IsDir() {
			continue
		}
		if n > last {
			last = n
		}
	}
	name := fmt.Sprintf("%03v", last+1)
	if err := os.Mkdir(name, 0755); err != nil {
		log.Printf("mkdir error for name(%v): %v\n", name, err)
		return
	}
	if err := createCpp(name); err != nil {
		log.Printf("createCPP error for name(%v): %v\n", name, err)
		return
	}
	if err := createPy(name); err != nil {
		log.Printf("createPy error for name(%v): %v\n", name, err)
		return
	}
}
