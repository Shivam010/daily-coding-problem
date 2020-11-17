package _001

import (
	"testing"
)

func TestSolution(t *testing.T) {
	type args struct {
		array []int
		k     int
	}
	tests := []struct {
		name string
		args args
		want bool
	}{
		{
			name: "one",
			args: args{
				array: []int{10, 15, 3, 7},
				k:     17,
			},
			want: true,
		},
		{
			name: "two",
			args: args{
				array: []int{2, 4},
				k:     5,
			},
			want: false,
		},
		{
			name: "three",
			args: args{
				array: []int{5},
				k:     5,
			},
			want: false,
		},
		{
			name: "four",
			args: args{
				array: []int{0, 0},
				k:     0,
			},
			want: true,
		},
		{
			name: "five",
			args: args{
				array: []int{4, 6},
				k:     10,
			},
			want: true,
		},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got := Solution(tt.args.array, tt.args.k); got != tt.want {
				t.Error("Solution() = got ", got, ", want ", tt.want)
			}
		})
	}
}
