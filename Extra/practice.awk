BEGIN{	
	class=""
	da=0;
	hr=0;
	bs=0;
	total=0;	
}

{
	bs=$6
	hr=0.15*bs
	da=0.4*bs
	total=bs+hr+da;
	
	if(total<5000)
		class=" 3rd class "
	if(total>5000 && total<10000)
		class=" 2nd class "
	if(total>10000 && total<15000)
		class=" 1st class "
	
	printf("\n%d  %s  %s  %s  %s  %d  %d  %d  %s  \n",$1,$2,$3,$4,$5,$6,hr,da,class);
}

END{
	;
}

