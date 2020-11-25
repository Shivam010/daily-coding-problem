// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

package _066

import (
	"math"
	"testing"
)

func TestBiasedCoin_Toss(t *testing.T) {
	defer func() {
		if c := recover(); c != nil {
			// maybe for some divide by zero
			t.Error("Recovered from hacky biased coin toss", c)
		}
	}()

	// a true biased coin toss
	trueBiased := BiasedCoin(true)
	result := map[bool]float64{}
	for i := 0; i < 10000000; i++ {
		result[trueBiased.Toss()]++
	}
	probRatio := math.Round(result[true] / result[false])
	if probRatio < 1 {
		t.Error("trueBiased: Ratio must be > 1, got", probRatio)
	}
	t.Logf("Biased over true: %v = %v:%v", probRatio, result[true], result[false])

	// a false biased coin toss
	falseBiased := BiasedCoin(false)
	result = map[bool]float64{}
	for i := 0; i < 10000000; i++ {
		result[falseBiased.Toss()]++
	}
	probRatio = math.Round(result[false] / result[true])
	if probRatio < 1 {
		t.Error("falseBiased: Ratio must be > 1, got", probRatio)
	}
	t.Logf("Biased over false: %v = %v:%v", probRatio, result[false], result[true])
}

func TestFairCoin_Toss(t *testing.T) {
	defer func() {
		if c := recover(); c != nil {
			// maybe for some divide by zero
			t.Error("Recovered from hacky fair coin toss", c)
		}
	}()

	// fair coin toss using true biased coin
	usingTrue := FairCoin{C: BiasedCoin(true)}
	result := map[bool]float64{}
	for i := 0; i < 10000000; i++ {
		result[usingTrue.Toss()]++
	}
	probRatio := math.Round(result[true] / result[false])
	if probRatio < 1 {
		t.Error("usingTrue.CoinToss: Ratio must be > 1, got", probRatio)
	}
	t.Logf("Fair toss using true biased coin: %v = %v:%v", probRatio, result[true], result[false])

	// fair coin toss using true biased coin
	usingFalse := FairCoin{C: BiasedCoin(true)}
	result = map[bool]float64{}
	for i := 0; i < 10000000; i++ {
		result[usingFalse.Toss()]++
	}
	probRatio = math.Round(result[false] / result[true])
	if probRatio < 1 {
		t.Error("usingFalse.CoinToss: Ratio must be > 1, got", probRatio)
	}
	t.Logf("Fair toss using false biased coin: %v = %v:%v", probRatio, result[false], result[true])
}
