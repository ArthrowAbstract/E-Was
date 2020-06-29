with open('4_CLASS_testa.txt','r') as f:
    count = 0
    for line in f:
        for word in line.split():
           if count%2 ==1:
               print(word)
           count+=1
