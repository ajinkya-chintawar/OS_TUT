BEGIN {
	da=0
	hr=0
}

{
	if($3 == "manager")
	{
		da = $6 * 0.4
		hr = $6 * 0.15
		printf("%d \t\t %s \t\t %s \t\t %d \t\t %d \t\t %d \n",$1,$2,$3,$6,da,hr)
	}
}


