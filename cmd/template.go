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

type SolutionData struct {
	Language string
	FilePath string
}

type ProblemData struct {
	Number    string
	Data      string
	Solutions []*SolutionData
}

func updateReadme(list []*ProblemData) error {
	file, err := os.Create("README.md")
	if err != nil {
		return err
	}
	return readmeTmpl.Execute(file, list)
}
