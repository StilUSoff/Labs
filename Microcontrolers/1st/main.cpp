int main (){
    int i;
    unsigned long int j;

    i=0;
    j=0;

    *(unsigned long*)(0x40023830) |= 0x40; //port G clocking
    *(unsigned long*)(0x40023830) |= 0x80; //port H clocking
    *(unsigned long*)(0x40023830) |= 0x100; //port I clocking

    for(i=0; i<4; i++){} //small delay for GPIOG get ready
    *(unsigned long*)(0x40021C00) = (*(unsigned long*)(0x40021C00) & (~0x00000080)) | (0x00000040); //Set PH3 
    *(unsigned long*)(0x40021C00) = (*(unsigned long*)(0x40021C00) & (~0x00002000)) | (0x00001000); //Set PH6 
    *(unsigned long*)(0x40021800) = (*(unsigned long*)(0x40021800) & (~0x00002000)) | (0x00001000); //Set PG6
    *(unsigned long*)(0x40021C00) = (*(unsigned long*)(0x40021C00) & (~0x00008000)) | (0x00004000); //Set PH7
    *(unsigned long*)(0x40022000) = (*(unsigned long*)(0x40022000) & (~0x00200000)) | (0x00100000); //Set PI10
    *(unsigned long*)(0x40021800) = (*(unsigned long*)(0x40021800) & (~0x00008000)) | (0x00004000); //Set PG7
    *(unsigned long*)(0x40021800) = (*(unsigned long*)(0x40021800) & (~0x00020000)) | (0x00010000); //Set PG8
    *(unsigned long*)(0x40021C00) = (*(unsigned long*)(0x40021C00) & (~0x00000020)) | (0x00000010); //Set PH2 	

    while(1){
        *(unsigned long*)(0x40021C14) |= 0x08; //PH3 on
        *(unsigned long*)(0x40021C14) |= 0x40; //TPH6 on
        for( j=0; j<1000000 ;j++ ){} //Delay
        *(unsigned long*)(0x40021C14) &= ~0x08; //PH3 off 
        *(unsigned long*)(0x40021C14) &= ~0x40; //PH6 off
        for( j=0; j<1000000 ;j++ ){} //Delay			
        *(unsigned long*)(0x40021C14) |= 0x80; //PH7 on	 
        *(unsigned long*)(0x40022014) |= 0x400; //PI10 on
        for( j=0; j<1000000 ;j++ ){} //Delay		
        *(unsigned long*)(0x40021C14) &= ~0x80; //PH7 off
        *(unsigned long*)(0x40022014) &= ~0x400; //PI10 off
        for( j=0; j<1000000 ;j++ ){} //Delay			
        *(unsigned long*)(0x40021814) |= 0x40; //PG6 on
        *(unsigned long*)(0x40021814) |= 0x80; //PG7 on
        for( j=0; j<1000000 ;j++ ){} //Delay	
        *(unsigned long*)(0x40021814) &= ~0x40; //PG6 off			
        *(unsigned long*)(0x40021814) &= ~0x80; //PG7 off
        for( j=0; j<1000000 ;j++ ){} //Delay				
        *(unsigned long*)(0x40021814) |= 0x100; //PG8 on
        *(unsigned long*)(0x40021C14) |= 0x04; //PH2 on
        for( j=0; j<1000000 ;j++ ){} //Delay					
        *(unsigned long*)(0x40021814) &= ~0x100; //PG8 off
        *(unsigned long*)(0x40021C14) &= ~0x04; //PH2 off
        for( j=0; j<2000000 ;j++ ){} //Delay
    }
}