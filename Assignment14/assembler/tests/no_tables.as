; A Valid assembly soruce file, with no tables
; Data
nums: .data 1, 2, 3, 4, 5, 6, 7, 8, 9

macro incNum
 mov #2, r10
 inc nums[r10]
endm

mov #3, r11
mov #-4, nums[r11]

incNum