// main package is the script which on running will setup a new
// daily problem directory
package main

import (
	"fmt"
	"io/ioutil"
	"log"
	"os"
	"path"
	"strconv"
)

func main() {
	dir, err := ioutil.ReadDir(".")
	if err != nil {
		log.Println("read dir error:", err)
		return
	}
	last := 0
	for _, dayD := range dir {
		n, err := strconv.Atoi(dayD.Name())
		if n == 0 || err != nil || !dayD.IsDir() {
			continue
		}
		if n > last {
			last = n
		}
	}
	newD := fmt.Sprintf("%03v", last+1)
	if err := os.Mkdir(newD, 0755); err != nil {
		log.Println("mkdir error", err)
		return
	}
	if err := createCPP(newD); err != nil {
		log.Println("createCPP error", err)
		return
	}
	if err := createPy(newD); err != nil {
		log.Println("createPy error", err)
		return
	}
}

func createCPP(dir string) error {
	data := fmt.Sprintf(cppTemplate, dir, dir, dir, dir)
	err := ioutil.WriteFile(path.Join(dir, "code.cpp"), []byte(data), 0644)
	if err != nil {
		return err
	}
	err = ioutil.WriteFile(path.Join(dir, "in.txt"), []byte("\n"), 0644)
	if err != nil {
		return err
	}
	return ioutil.WriteFile(path.Join(dir, "out.txt"), []byte("\n"), 0644)
}

func createPy(dir string) error {
	data := fmt.Sprintf(pyTemplate, dir, dir)
	return ioutil.WriteFile(path.Join(dir, "code.py"), []byte(data), 0755)
}

const cppTemplate = `/*
Daily Coding Challenge #%v
---------------------------


Run Using
---------
g++ %v/code.cpp -o bin/out && ./bin/out < %v/in.txt > %v/out.txt
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mk make_pair
#define pb push_back
#define Pi pair<int, int>
#define Pl pair<long long, long long>
#define vi vector<int>
#define vl vector<long long>
#define vb vector<bool>
#define vp vector<pair<int, int>>
#define vpl vector<pair<long long, long long>>
#define F first
#define S second
#define min(a, b) ((a < b) ? a : b)
const ll mod = 1000000007;

int main() {
	
}
`

const pyTemplate = `#!/usr/bin/env python3.7

"""
Daily Coding Challenge #%v
---------------------------


Run Using
---------
./%v/code.py
"""


`
