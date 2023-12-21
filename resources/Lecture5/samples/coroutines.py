# Python program to generate numbers in a 
# range using yield

def rangeN(a, b):
	i = a
	while (i < b):
		yield i
		i += 1 # Next execution resumes 
				# from this point 

for i in rangeN(1, 5):
		print(i)


#this code is similar to
# for(int i=1;i<5;i=range(1,5))
# {
#     print(i)
# }