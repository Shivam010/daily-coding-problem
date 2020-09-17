package main

import (
	"io/ioutil"
	"os"
	"path"
	"text/template"
)

var (
	dotPyTmpl  = template.Must(template.ParseFiles(path.Join("cmd", "py.gotxt")))
	dotCppTmpl = template.Must(template.ParseFiles(path.Join("cmd", "cpp.gotxt")))
	readmeTmpl = template.Must(template.ParseFiles(path.Join("cmd", "readme.gomd")))
)

func createCpp(name string) error {
	file, err := os.Create(path.Join(name, "code.cpp"))
	if err != nil {
		return err
	}
	if err := dotCppTmpl.Execute(file, name); err != nil {
		return err
	}
	err = ioutil.WriteFile(path.Join(name, "in.txt"), []byte("\n"), 0644)
	if err != nil {
		return err
	}
	return ioutil.WriteFile(path.Join(name, "out.txt"), []byte("\n"), 0644)
}

func createPy(name string) error {
	file, err := os.Create(path.Join(name, "code.py"))
	if err != nil {
		return err
	}
	if err := file.Chmod(0755); err != nil {
		return err
	}
	return dotPyTmpl.Execute(file, name)
}

// SolutionData represents a unit solution block
type SolutionData struct {
	Language string
	FilePath string
}

// ProblemData represents a unit problem that is solved
type ProblemData struct {
	Number    string
	Data      string
	Unsolved  []string
	Solutions []*SolutionData
}

// Data represents the final object for the template containing
// solved problems' data and unsolved one's number.
type Data struct {
	Problems []*ProblemData
	Unsolved []string
	// functions
	Last   func(sl []string) string
	Missed func(sl []string) []string
}

func updateReadme(data *Data) error {
	data.Last = func(sl []string) string {
		if len(sl) == 0 {
			return ""
		}
		return sl[len(sl)-1]
	}
	data.Missed = func(sl []string) []string {
		if len(sl) == 0 {
			return sl
		}
		return sl[:len(sl)-1]
	}
	file, err := os.Create("README.md")
	if err != nil {
		return err
	}
	return readmeTmpl.Execute(file, data)
}
