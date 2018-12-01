BEGIN { 
	OFS="^" ;
}
 
{
	for (i=1; i <= NF; i++)
		printf("%s%s", $i, (i==NF) ? ORS : OFS) 
}

