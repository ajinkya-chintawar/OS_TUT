BEGIN{
printf("\n");
printf("________________________________");
printf("\n");
printf("\t\tSHOPPING CART");
printf("\n");
printf("________________________________");
printf("\n");
printf("SR NO.  PARTICULARS  QUANTITY   AMOUNT   TOTAL");
tot=0;
amt=0;
disc=0.0;
pay=0.0;
}
{
amt=$3*$4;
printf("\n");
printf(" \t%d \t%s \t%d \t%d\t %d",$1,$2,$3,$4,amt);
printf("\n");
tot+=amt;
}
END{
printf("\n________________________________\n");
disc=tot*(5/100);
pay=tot-disc;
printf("Total    :%d",tot);
printf("\n");
printf("Discount :%f",disc);
printf("\n");
printf("Amount   :%f",pay);
printf("\n");
printf("________________________________");
printf("\n");
printf("\nTHANK YOU.....!!!!");
printf("\n");
}
INPUT FILE :
1|ABC|4|20
2|XYZ|5|30
3|LMN|6|20
OUTPUT :
sanjam@sanjam-VirtualBox:~/Desktop$ awk -F "|" -f ash1.awk ash1.txt

________________________________
		SHOPPING CART
________________________________
SR NO.  PARTICULARS  QUANTITY   AMOUNT   TOTAL
 	1 	ABC 	4 	20	 80

 	2 	XYZ 	5 	30	 150

 	3 	LMN 	6 	20	 120

________________________________
Total    :350
Discount :17.500000
Amount   :332.500000
________________________________

THANK YOU.....!!!!
sanjam@sanjam-VirtualBox:~/Desktop$ 

