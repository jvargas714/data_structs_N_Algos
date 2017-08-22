#!/bin/bash
## to answer questions

filename='./more_quesitons.txt'
num_questions=$(grep ^Q $filename | wc -l)
cont="y"


while [ $cont == "y" ]
do
    printf '\n\n'
    echo "There are $num_questions questions, enter a question number i.e: 3"
    read qnum
    echo "you selected $qnum"

    grep ^Q$qnum more_quesitons.txt 

    printf "\nPress Enter for answer...\n"
    read enter

    grep ^A$qnum -A $(cat $filename|wc -l)  more_quesitons.txt | awk /^A/,/^-/'{print}'
    printf '\nContinue(y/n)??\n'
    read cont
done