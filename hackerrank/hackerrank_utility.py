import difflib, time, sys 

# globals
ASSESSMENTS = './assessments/'

def check_result(ans, prblm_name, input_line_offset=0): 
	'''
		takes output of answer and compares against expected answer 
		ans: (str), (file)
	'''
	no_correct = 0 
	no_wrong = 0 
	output = open('./assessments/'+prblm_name+'.csv', 'w+')
	output.write('Line Number,Input,Expected Output,Output,Result\n')
	expected_ans = open('./output/'+prblm_name+'.out', 'r')
	input_val = open('./input/'+prblm_name+'.in', 'r')

	# skip input lines to skip over setup input values 
	for i in range(input_line_offset):
		input_val.readline()

	for ln, (inval, exp_line, ans_line) in enumerate( zip(input_val, expected_ans, ans) ):
		ln+=1 + input_line_offset
		if ans_line.strip() != exp_line.strip():
			no_wrong += 1
			entry = f'{ln},{inval.strip()},{exp_line.strip()},{ans_line.strip()},Wrong'
			output.write(entry+'\n')
		else:
			entry = f'{ln},{inval.strip()},{exp_line.strip()},{ans_line.strip()},Corrent'
			no_correct += 1
			# output.write(entry+'\n')
		
	summary = f'\n\n\nResults:\nNumber Correct,Number Wrong,% Correct\n'\
					f'{no_correct},{no_wrong},{round(no_correct/(no_correct+no_wrong)*100, 3)}%\n'
	output.write(summary)
	output.close() 
	expected_ans.close()
	input_val.close()

def time_execution(func_obj, args=None):
	'''
		times execution of provided function 
		args would be a tuple of the arguments that would be used for the function 
	'''
	try:
		if not args:
			t0 = time.clock()
			func_obj()
			t1 = time.clock()
		else:
			t0 = time.clock()
			func_obj(*args)
			t1 = time.clock()
	except Exception as e:
		print(f'Error executing function object.\n\ntype: \
			      	{sys.exc_info()[0]}, \n\nvalue:{sys.exc_info()[1]}')
	
	return str(f'Time of Execution: {round((t1-t0)*1000, 3)}msecs\n')
