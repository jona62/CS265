paste -d '|' listOfUserIds.txt listOfNames.txt listOfEmails.txt listOfAddresses.txt |  awk -f formatFiles.awk > Students.txt
sed -i -e 's/|/ /g' Students.txt

cp Students.txt ../