// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// Package main contains the script which on running will setup
// the new daily problem directory/files, and finally update the
// README file using Github Actions
package main

import (
	"fmt"
	"io/ioutil"
	"log"
	"os"
	"path"
	"strconv"
	"strings"
	"time"
)

// startDate: day before the first date of solving problems i.e September 02, 2020 IST
var startDate time.Time

// pwd: current working director to save all challenges, it is stored in
// the file `cmd/pwd`.
// It will not change until the days' past Sept 03 reaches it's threshold
var pwd = struct {
	Value string // actual directory
	Lower int    // lower limit of the range
	Upper int    // upper limit of the range
}{}

func init() {
	ist, _ := time.LoadLocation("Asia/Kolkata")
	startDate = time.Date(2020, time.September, 2, 0, 0, 0, 0, ist)
	data, err := ioutil.ReadFile("cmd/pwd")
	if err != nil {
		log.Panicln("storage file `cmd/pwd` has been compromised, error:", err)
	}
	pwd.Value = string(data)
	parts := strings.Split(pwd.Value, "-")
	pwd.Lower, err = strconv.Atoi(parts[0])
	if err != nil {
		log.Panicln("storage file `cmd/pwd` has been compromised, error:", err)
	}
	pwd.Upper, err = strconv.Atoi(parts[1])
	if err != nil {
		log.Panicln("storage file `cmd/pwd` has been compromised, error:", err)
	}
}

func main() {
	if os.Getenv("push") != "" {
		// Push event
		// Update the readme
		updateReadme()
	}
	if os.Getenv("cron") != "" {
		// Cron job: every day
		// Setup new problem directory
		setupNewDirectory()
		// and update the readme
		updateReadme()
	}
	// update `cmd/pwd` file
	if err := ioutil.WriteFile("cmd/pwd", []byte(pwd.Value), 0644); err != nil {
		log.Panicln("Something went wrong updating `cmd/pwd`, error:", err)
	}
}

func updateReadme() {
	fmt.Println("Updating the README")
	list, err := ioutil.ReadDir(pwd.Value)
	if err != nil {
		log.Panicln("read dir error:", err)
	}

	last := 0
	missed := make([]string, 0, len(list))

	for _, dir := range list {
		name := dir.Name()
		n, err := strconv.Atoi(name)
		if n == 0 || err != nil || !dir.IsDir() {
			continue
		}
		dirPath := path.Join(pwd.Value, name)

		// read <dirPath>/README.md
		_data, err := ioutil.ReadFile(path.Join(dirPath, "README.md"))
		if err != nil {
			log.Panicln("read dir error:", err)
		}
		data := string(_data)
		notYetUpdated := strings.Contains(data, "Not yet checked or started")
		if strings.Contains(data, "> Check mail") && notYetUpdated {
			// missed
			missed = append(missed, name)
			continue
		}

		// if readme is not yet updated
		if notYetUpdated {
			onlyQues := data
			// remove header section
			if ind := strings.Index(onlyQues, "_<br>"); ind != -1 {
				onlyQues = onlyQues[ind+6:]
			}
			// remove footer section
			if ind := strings.Index(onlyQues, "[]()"); ind != -1 {
				onlyQues = onlyQues[:ind]
			}
			// remove solutions section
			if ind := strings.Index(onlyQues, "**Solution(s)**"); ind != -1 {
				onlyQues = onlyQues[:ind]
			}
			if err := renderTemplate(
				problemReadmeTmp,
				path.Join(dirPath, "README.md"),
				&ProblemData{
					Name:      name,
					Data:      onlyQues,
					Date:      startDate.AddDate(0, 0, n).Format("January 02, 2006"),
					Solutions: listSolutions(name, dirPath),
				},
			); err != nil {
				return
			}
		}

		if last < n {
			last = n
		}
	}
	if last == 0 {
		last = pwd.Lower - 1
	}

	next := ""
	if len(missed) > 0 {
		next = missed[len(missed)-1]
		missed = missed[:len(missed)-1]
	}
	// update main readme
	if err := renderTemplate(
		readmeTmp,
		"README.md",
		&Data{
			Days:       int(time.Since(startDate.Add(21*time.Hour))) / int(time.Hour*24),
			Solved:     last,
			Next:       next,
			Missed:     missed,
			Noteworthy: listNoteworthy(),
		},
	); err != nil {
		return
	}
}

func setupNewDirectory() {
	fmt.Println("Setting up new Problem directory")
	list, err := ioutil.ReadDir(pwd.Value)
	if err != nil {
		log.Panicln("read dir error:", err)
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
	if last == pwd.Upper {
		// change pwd
		pwd.Lower, pwd.Upper = pwd.Lower+50, pwd.Upper+50
		pwd.Value = fmt.Sprintf("%v-%v", pwd.Lower, pwd.Upper)
		if err = os.Mkdir(pwd.Value, 0755); err != nil {
			log.Panicln("Something went wrong creating new pwd", pwd, "error:", err)
		}
	}
	name := fmt.Sprintf("%03v", last+1)
	fullPath := path.Join(pwd.Value, name)

	// C++ code structure
	cppN := path.Join(fullPath, "c++")
	if err := os.MkdirAll(cppN, 0755); err != nil {
		log.Panicf("mkdir error for path(%v): %v\n", cppN, err)
	}
	if err := renderTemplate(cppTmp,
		path.Join(cppN, "code.cpp"),
		map[string]interface{}{"name": name, "path": fullPath},
	); err != nil {
		return
	}

	// go code structure
	goN := path.Join(fullPath, "go")
	if err := os.MkdirAll(goN, 0755); err != nil {
		log.Panicf("mkdir error for path(%v): %v\n", goN, err)
	}
	if err := renderTemplate(goTmp, path.Join(goN, "code.go"), name); err != nil {
		return
	}
	if err := renderTemplate(goTestTmp, path.Join(goN, "code_test.go"), name); err != nil {
		return
	}

	// update problem readme
	if err := renderTemplate(
		problemReadmeTmp,
		path.Join(fullPath, "README.md"),
		&ProblemData{
			Name: name,
			Data: "> Check mail\n\n",
			Date: startDate.AddDate(0, 0, last+1).Format("January 02, 2006"),
		},
	); err != nil {
		return
	}
}

var pwdList = []string{"001-050", "051-100", "101-150"}

func listNoteworthy() []string {
	data, err := ioutil.ReadFile("note-worthy")
	if err != nil {
		log.Panicln("storage file `note-worthy` has been compromised, error:", err)
	}
	names := strings.Split(string(data), "\n")

	list := make([]string, 0, len(names))
	for _, name := range names {
		if name == "" {
			continue
		}
		no, err := strconv.Atoi(name)
		if err != nil {
			log.Panicln("error for name:", name, "error:", err)
		}
		name := fmt.Sprintf("%03v", no)
		dirPath := path.Join(pwdList[(no-1)/50], name)

		_data, err := ioutil.ReadFile(path.Join(dirPath, "README.md"))
		if err != nil {
			log.Panicln("read dir error:", err)
		}
		data := string(_data)
		// remove footer from data
		if ind := strings.Index(data, "[]()"); ind != -1 {
			data = data[:ind]
		}
		for _, sol := range listSolutions(name, dirPath) {
			data = strings.ReplaceAll(data, sol.FilePath, path.Join(dirPath, sol.FilePath))
		}
		list = append(list, data)
	}

	return list
}

func listSolutions(question, dirPath string) []*SolutionData {

	files, err := ioutil.ReadDir(dirPath)
	if err != nil {
		log.Panicf("read dir error for name(%v): %v\n", question, err)
	}

	solList := make([]*SolutionData, 0, 2)
	for _, solDir := range files {
		name := solDir.Name()
		if !solDir.IsDir() {
			continue
		}
		lang, filePath := "", "code"
		switch name {
		case "python":
			lang = "Python"
			filePath += ".py"
		case "c++":
			lang = "C++"
			filePath += ".cpp"
		case "go":
			lang = "Golang"
			filePath += ".go"
		}
		solList = append(solList, &SolutionData{
			Language: lang,
			FilePath: path.Join(name, filePath),
		})
	}
	return solList
}
