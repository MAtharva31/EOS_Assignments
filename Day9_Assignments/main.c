#include"circle.h"
#include"rectangle.h"

int main(void){
	int radius = 5,len = 10,bred = 15,num = 25;
	printf("Area of circle whose radius %d is %d\n",radius, area_of_circle(radius));
	printf("Circumference of circle whose radius %d is %d\n",radius, circumference_of_circle(radius));
	printf("Area of Rectangle whose Length %d & Breadth %d is %d\n",len,bred,area_of_rect(len,bred));
	printf("Perimeter of Rectangle whose Length %d & Breadth %d sd %d\n",len,bred,peri_of_rect(len,bred));
	printf("Square of %d is %d\n",num,square(num));

	return 0;
}
