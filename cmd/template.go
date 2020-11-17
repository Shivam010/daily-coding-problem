package main

import (
	log "log"
	"os"
	"path"
	"text/template"
)

var (
	// all templates
	goTmp            = template.Must(template.ParseFiles(path.Join("cmd", "templates", "go.tmp")))
	cppTmp           = template.Must(template.ParseFiles(path.Join("cmd", "templates", "c++.tmp")))
	goTestTmp        = template.Must(template.ParseFiles(path.Join("cmd", "templates", "go_test.tmp")))
	readmeTmp        = template.Must(template.ParseFiles(path.Join("cmd", "templates", "readme.tmp")))
	problemReadmeTmp = template.Must(template.ParseFiles(path.Join("cmd", "templates", "problem-readme.tmp")))
)

// SolutionData represents a unit solution block
type SolutionData struct {
	Language string
	FilePath string
}

// ProblemData represents a unit problem that is solved
type ProblemData struct {
	Name      string
	Data      string
	Date      string
	Solutions []*SolutionData
}

// ReadmeData represents the statistic data to show in main README
type Data struct {
	Days       int
	Solved     int
	Next       string
	Missed     []string
	LastSolved string
}

// renderTemplate: renders the template `tmp` using `data` into the file at location `into`
func renderTemplate(tmp *template.Template, into string, data interface{}) error {
	file, err := os.Create(into)
	if err != nil {
		log.Printf("renderTemplate: file(%v) create error: %v\n", into, err)
		return err
	}
	if err := tmp.Execute(file, data); err != nil {
		log.Printf("renderTemplate: error for %v: %v\n", into, err)
		return err
	}
	return nil
}
