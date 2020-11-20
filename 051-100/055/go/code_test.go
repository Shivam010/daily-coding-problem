// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

package _055_test

import (
	"github.com/Shivam010/daily-coding-problem/051-100/055/go"
	"sort"
	"strconv"
	"testing"
)

type iTester interface {
	Helper()
	Errorf(format string, args ...interface{})
}

func must(t iTester) func(in string, err error) string {
	t.Helper()
	return func(in string, err error) string {
		if err != nil {
			t.Errorf("error occurred = %v", err)
		}
		return in
	}
}

func validityTest(t *testing.T, sh _055.UrlShortener) []string {
	t.Helper()
	gotIds := make([]string, 0, len(urls))
	t.Run("validity-test", func(t *testing.T) {
		must := must(t)
		for _, url := range urls {
			got := must(sh.Shorten(url))
			gotIds = append(gotIds, got)
			ori := must(sh.Restore(got))
			if ori != url {
				t.Errorf("Restore(id), got = %v, want %v", ori, url)
			}
		}
	})
	return gotIds
}

func TestUrlShortener_Default(t *testing.T) {
	sh := _055.NewUrlShortener()
	gotIds := validityTest(t, sh)
	t.Run("randomize-test", func(t *testing.T) {
		if sort.StringsAreSorted(gotIds) {
			t.Errorf("Must be randomize")
		}
	})
	t.Run("size-6", func(t *testing.T) {
		for _, id := range gotIds {
			if len(id) != 6 {
				t.Errorf("Must be of length 6, got = %v", id)
			}
		}
	})
	t.Run("re-validate", func(t *testing.T) { validityTest(t, sh) })
}

func TestUrlShortener_Size10(t *testing.T) {
	sh := _055.NewUrlShortener(_055.SetShortUrlSize(10))
	gotIds := validityTest(t, sh)
	t.Run("randomize-test", func(t *testing.T) {
		if sort.StringsAreSorted(gotIds) {
			t.Errorf("Must be randomize")
		}
	})
	t.Run("size-10", func(t *testing.T) {
		for _, id := range gotIds {
			if len(id) != 10 {
				t.Errorf("Must be of length 10, got = %v", id)
			}
		}
	})
	t.Run("re-validate", func(t *testing.T) { validityTest(t, sh) })
}

func TestUrlShortener_Sequential(t *testing.T) {
	sh := _055.NewUrlShortener(_055.SetGeneratorAlgorithm(_055.Sequential))
	gotIds := validityTest(t, sh)
	t.Run("sequence-test", func(t *testing.T) {
		if !sort.StringsAreSorted(gotIds) {
			t.Errorf("Must be sorted")
		}
	})
	t.Run("size-6", func(t *testing.T) {
		for _, id := range gotIds {
			if len(id) != 6 {
				t.Errorf("Must be of length 6, got = %v", id)
			}
		}
	})
	t.Run("re-validate", func(t *testing.T) { validityTest(t, sh) })
}

func TestUrlShortener_Many(t *testing.T) {
	list := make([]string, 10e5)

	for i := range list {
		list[i] = "https://base.str/" + strconv.Itoa(i)
	}
	for name, sh := range map[string]_055.UrlShortener{
		"randomize":  _055.NewUrlShortener(_055.SetGeneratorAlgorithm(_055.Randomize)),
		"sequential": _055.NewUrlShortener(_055.SetGeneratorAlgorithm(_055.Sequential)),
	} {
		t.Run(name, func(t *testing.T) {
			must := must(t)
			for _, url := range list {
				if got := must(sh.Restore(must(sh.Shorten(url)))); url != got {
					t.Errorf("Restore(Shorten(url)), got = %v, want %v", got, url)
				}
			}
		})
	}
}

func TestUrlShortenener_Negative(t *testing.T) {
	t.Run("empty", func(t *testing.T) {
		sh := _055.NewUrlShortener()
		if must(t)(sh.Shorten("")) != "" {
			t.Error("Shorten: empty should be returned")
		}
		if must(t)(sh.Restore("")) != "" {
			t.Error("Restore: empty should be returned")
		}
	})
	t.Run("invalid-algo", func(t *testing.T) {
		sh := _055.NewUrlShortener(_055.SetGeneratorAlgorithm(3))
		if _, err := sh.Shorten("3"); err != _055.ErrUnsupportedAlgo {
			t.Error("ErrUnsupportedAlgo should be returned")
		}
	})
	t.Run("not-found", func(t *testing.T) {
		sh := _055.NewUrlShortener()
		if _, err := sh.Restore("3"); err != _055.ErrNotFound {
			t.Error("ErrUnsupportedAlgo should be returned")
		}
	})
	t.Run("storage-full", func(t *testing.T) {
		sh := _055.NewUrlShortener(_055.SetShortUrlSize(1))
		for i := 0; i < 62; i++ {
			must(t)(sh.Shorten(strconv.Itoa(i)))
		}
		if _, err := sh.Shorten("63"); err != _055.ErrStorageFull {
			t.Error("ErrStorageFull should be returned")
		}
	})
}

func BenchmarkUrlShortener(b *testing.B) {
	must := must(b)
	for name, sh := range map[string]_055.UrlShortener{
		"randomize":  _055.NewUrlShortener(_055.SetGeneratorAlgorithm(_055.Randomize)),
		"sequential": _055.NewUrlShortener(_055.SetGeneratorAlgorithm(_055.Sequential)),
	} {
		b.Run(name, func(b *testing.B) {
			var list []string
			b.Run("shorten", func(b *testing.B) {
				list = make([]string, b.N)
				for i := 0; i < b.N; i++ {
					url := strconv.Itoa(i)
					list[i] = must(sh.Shorten(url))
				}
			})
			ln := len(list)
			b.Run("restore", func(b *testing.B) {
				for i := 0; i < b.N; i++ {
					must(sh.Restore(list[i%ln]))
				}
			})
		})
	}
}

// Total urls = 121
// Almost all urls are extracted from https://stackify.com/learn-go-tutorials/ using https://iwebtool.com/link_extractor
var urls = []string{
	"notfound.com",
	"google.com",
	"github.com",
	"github.com/Shivam010",
	"https://www.eduonix.com/courses/Software-Development/the-go-programming-language-guide-code-like-a-pro",
	"https://stackify.com/?tag=logs,logging",
	"https://stackify.com/retrace-error-monitoring/",
	"https://miek.nl/go/",
	"https://stackify.com/node-js-developer-tools/",
	"https://www.eduonix.com/courses/Software-Development/the-go-programming",
	"https://stackify.com/privacy-policy/",
	"https://stackify.com/best-website-load-testing-services/",
	"https://stackify.com/stackify-webinars/",
	"https://stackify.com/blog/",
	"https://www.codementor.io/go",
	"http://www.golangprograms.com/advance-programs.html",
	"https://www.pluralsight.com/courses/go",
	"https://stackify.com/content/tutorials/",
	"https://stackify.com/?tag=exception,exceptions,error,errors",
	"http://devs.cloudimmunity.com/gotchas-and-common-mistakes-in-go-golang/index.html",
	"https://stackify.com/windows-server-performance-monitoring-best-practices/",
	"https://stackify.com/retrace-apm-dotnet/",
	"https://stackify.com/retrace-log-management/",
	"https://stackify.com/content/net-core/",
	"https://golangbot.com/learn-golang-series/",
	"https://stackify.com/retrace-azure-monitoring/",
	"https://stackify.com/stackify-developer-ebooks/",
	"https://stackify.com/performance-tuning-in-sql-server-find-slow-queries/",
	"https://stackify.com/content/azure/",
	"https://tour.golang.org/welcome/1",
	"http://www.golangbootcamp.com/book",
	"https://stackify.com/retrace-apm-python/",
	"https://stackify.com/retrace-apm-php/",
	"https://stackify.com/",
	"https://docs.stackify.com/v1/docs?_ga=2.2045431.795068548.1606150356-1374364069.1597069964",
	"https://stackify.com/w3wp-high-cpu-usage/",
	"https://stackify.com/?page_id=6455",
	"https://stackify.com/node-js-framework/",
	"https://stackify.com/why-stackify/#roi-calculator",
	"https://appliedgo.com/p/mastergo/",
	"https://stackify.com/continuous-application-improvement-for-devops/",
	"https://stackify.com/retrace-logging-error-tracking/",
	"https://stackify.com/contact-us/",
	"https://stackify.com/retrace-aws-monitoring/",
	"https://stackify.com/developers/",
	"https://stackify.com/ruby-on-rails-blogs-youtube-channels/",
	"https://s1.stackify.com/?_ga=2.236312007.795068548.1606150356-1374364069.1597069964",
	"https://stackify.com/pricing/",
	"https://gowebexamples.com/",
	"https://www.udemy.com/go-the-complete-developers-guide/?siteID=Fh5UMknfYAU-Y3GfqGCjr2HM72QV_v2NLg&LSNPUBID=Fh5UMknfYAU",
	"https://stackify.com/best-5-tools-for-node-js-monitoring/",
	"https://ideas.stackify.com/?_ga=2.5256949.795068548.1606150356-1374364069.1597069964",
	"https://s1.stackify.com/account/createclient/?fromretrace=1",
	"https://stackify.com/stackify-case-studies/",
	"https://ideas.stackify.com/?_ga=2.150793076.334670315.1525095666-1540781610.1523310878",
	"https://stackify.com/retrace-code-profiling/",
	"https://stackify.com/retrace-application-performance-management/",
	"https://stackify.com/retrace-real-user-monitoring/",
	"https://www.lynda.com/Go-training-tutorials/7052-0.html",
	"https://stackify.com/node-js-blogs-youtube-channels/",
	"https://stackify.com/terms-conditions/",
	"https://stackify.com/careers/",
	"https://stackify.com/career/",
	"https://www.infoworld.com/article/3290470/google-go/go-tutorial-get-started-with-Google-go.html",
	"https://teamtreehouse.com/library/go-language-overview?irgwc=1&click_id=3Cj04NwSASX8XTu0QqweyRdEUkg0qqT4NyGqRE0&iradid=228915&ircid=3944&irpid=383034&iradname=Online%20Tracking%20Link&iradtype=ONLINE_TRACKING_LINK&iradsize=&irmpname=Hackr.io&irmptype=mediapartner&utm_source=ir&cid=4612",
	"https://stackify.com/how-to-monitor-a-windows-process/",
	"https://stackify.com/retrace-apm-nodejs/",
	"https://stackify.com/?tag=asp.net,net-core",
	"https://stackify.com/how-to-monitor-website-performance/",
	"https://stackify.com/news-press/",
	"https://www.toptal.com/go/go-programming-a-step-by-step-introductory-tutorial",
	"https://gophercises.com/",
	"https://s1.stackify.com/account/createclient/?fromretrace=1&_ga=2.117403919.841090771.1606836463-1374364069.1597069964",
	"https://gobyexample.com/",
	"https://stackify.com/retrace-apm-java/",
	"https://stackify.com/microsoft-application-insights-alternative/",
	"https://stackify.com/technologies/",
	"https://stackify.com/content/DevOps/",
	"https://www.youtube.com/channel/UCnxYNQDtTr_ZYUnMjeACfCg",
	"https://awesome-go.com/",
	"https://twitter.com/Stackify",
	"https://stackify.com/retrace-apm-ruby/",
	"https://hackernoon.com/basics-of-golang-for-beginners-6bd9b40d79ae",
	"https://stackify.com/retrace/",
	"https://pragmacoders.com/t/golang-tutorials/",
	"https://stackify.com/guest-blogging-guidelines/",
	"https://www.facebook.com/Stackify/",
	"https://www.ardanlabs.com/categories/go-programing/",
	"https://www.linkedin.com/company/stackify/",
	"https://stackify.com/content/AWS/",
	"https://stackify.com/learn-javascript-tutorials/",
	"https://stackify.com/support/",
	"https://stackify.com/continuous-application-improvement-for-developers/",
	"https://stackify.com/content/developer/",
	"https://www.techgig.com/skilltest/go",
	"https://stackify.com/prefix/",
	"https://stackify.com/?tag=performance,profiler,apm",
	"https://golangcode.com/",
	"https://stackify.com/how-to-monitor-iis-performance/",
	"https://stackify.com/?tag=monitoring,apm",
	"http://www.golang-book.com/",
	"https://stackify.com/retrace-deployment-tracking/",
	"https://stackify.com/new-relic-alternatives-for-developers/",
	"https://stackify.com/stackify-security-information/",
	"https://golangtutorials.blogspot.com/2011/05/table-of-contents.html",
	"https://stackify.com/learn-go-tutorials/tel:18168885055",
	"https://stackify.com/retrace-app-monitoring/",
	"https://cta-redirect.hubspot.com/cta/redirect/207384/a2ceb3bf-6dc4-4881-b74a-87bade4873fa",
	"https://stackify.com/stackify/",
	"https://www.cosmiclearn.com/go/",
	"https://stackify.com/demo-request",
	"https://golang.org/dl/",
	"https://www.youtube.com/stackify",
	"https://stackify.com/content/java/",
	"https://www.tutorialspoint.com/go/",
	"https://www.safaribooksonline.com/library/view/ultimate-go-programming/9780134757476/",
	"https://reactdom.com/go",
	"https://docs.stackify.com/v1/docs",
	"https://stackify.com/gdpr/",
	"https://stackify.com/about/",
	"https://stackify.com/?tag=cloud,azure,aws",
}
