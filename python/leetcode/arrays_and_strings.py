import sys
sys.path.append('..')
import utility as ut

# start at i = 0 work to len - 1
# for each i slice to get the sub_range, 
# from there get the min and max, check if they are 1 apart 
# if that dont work remove either min or max try again 
def findLHS(nums: list) -> int:
	for i in range(len(nums)):
		sub_range = nums[i:]
		mn = min(sub_range)
		mx = max(sub_range)
		if mx - mn <= 1:
			return len(sub_range)
		nums.remove(mn)



if __name__ == '__main__':
	nums = [1,3,2,2,5,2,3,7]
	expected = 5
	print(f"result: {findLHS(nums)}, expected: {expected}")

