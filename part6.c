
#include <assert.h>

//extract the 8-bit exponent field of single precision floating point number f 
//and return it as an unsigned byte
unsigned char
get_exponent_field(float f) 
{

	

	// this will convert the float to a integer pointer
	unsigned int* rei = (unsigned int*) &f;

	// then you move the sign out 
	*rei<<=1;

	// cast the int back into a char and grab the third byte in the memory storage
	return *((unsigned char*) rei +3);

	// another method - cast the float as an int, shift left once to remove the sign
	// techniquely this is unnecessary because it is already unsigned, but then next
	// shift it all right 24 times to get rid of the mantissa
	//unsigned int* expo  = ( unsigned int*) &f;
	//*expo = *expo <<1;
	//*expo = *expo >> 24;
	//return *(unsigned char*) expo;


}

//clear the most significant b bits of unsigned integer number
//return the resulting value
//As an example, suppose unsigned int number = 0xffff0000; int b= 15
//then the correct return value is 65536
//if b = 30, then the return value is 0
//if b = 40, the return value should also be zero
unsigned int
clear_msb(unsigned int number, int b)
{

	unsigned int num ;
	if (b<= 32){
		// shift right b amount of times to get something like ox0000ffff to clear insignificant bits
		num = (0xffffffff>>b);
		// then you will check the bits to see if which will match up with num
		return number &num;

		// here is another more obvious method
		// basically shift left b amount of times then shift
		// right b amount of times to clear the insignificant bits
		//num = number <<b;
	 	//num = num>>b;
		//return num;
	}else{
		// return zero if the number of bit shifts is out of bounds
		return 0;
	}

}

//given an array of bytes whose length is array_size (bytes), treat it as a bitmap (i.e. an array of bits),
//and return the bit value at index i (from the left) of the bitmap.
//As an example, suppose char array[3] = {0x00, 0x1f, 0x12}, the corresponding
//bitmap is 0x001f12, thus,
//the bit at index 0 is bitmap[0] = 0
//the bit at index 1 is bitmap[1] = 0
//...
//the bit at index 11 is bitmap[11] = 1
//the bit at index 12 is bitmap[12] = 1
//...
//the bit at index 16 is bitmap[16] = 0
//...
unsigned char
bit_at_index(unsigned char *array, int array_size, int i)
{
	
	
	// this if statement is not 100% necessary to complete the grading script but
	// the logic is necessary  because you should make sure i is not out of bounds
	if (i >= array_size*8){
	unsigned char c;
		return c;
	}

	// finding the location in the char array to access the element. Will always round down
	//unsigned int pointOfChar = i/8;
	// finding the location of the bit in the byte 
	//unsigned int reminder = i%8;
	// assign a char to the point in the array of the byte we need to extract the bit from
	//unsigned char a = array[pointOfChar];
	// you will shift the char bits left by the reminder
	//a = a<<(reminder);
	// then shift all the bits right 7 times so the only bit left is the one at 
	// the location you designated with i
	//a = a >>(7);
	// return the bit with the bit boolean operator & with 1 to check if it is 1
	//return (a&1);
	
	// I did the same thing as the comments above but in one step
	return (unsigned char) ((array[i/8]<<(i%8))>>7)&1;



}
