import pdb

def swap(arr, i, j):
	tmp = arr[i] 
	arr[i] = arr[j] 
	arr[j] = tmp 

def swap_cpy(arr, i, j):
	tmp = arr[:]
	swap(tmp, i, j)
	return tmp

def removeDuplicates(nums):
	sz = len(nums)
	if not sz:
		return 0
	if sz == 1:
		return 1

	offset = 0 
	cnt = 0 
	i = offset+1
	while i<sz:
		if nums[offset] == nums[i]:
			cnt+=1
			i+=1
		else:
			del nums[offset:offset+cnt]
			sz-=cnt
			cnt=0
			offset+=1
			i=offset+1
	del nums[offset:offset+cnt]
	return len(nums)

#TODO 
def _swap(nums, i, k, cnt):
	sz=len(nums)
	cnt+=1
	if cnt==(sz-1):
		return
	j=i+k
	if j>=sz:
		j-=sz
	swap(nums, i, j)
	print(f'nums:{nums}')
	_swap(nums, j, k, cnt)
	

# TODO 
def rotateArrayR(nums, k):
	# take a modulus to get rotation for one time around 
	 _swap(nums, 0, k, 0)

# TODO 
def rotateArrayL(nums, k):
	pass

x = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17] 
k = 1

print (f'before:{x}')
rotateArrayR(x, k)
print(f'after:{x}')
