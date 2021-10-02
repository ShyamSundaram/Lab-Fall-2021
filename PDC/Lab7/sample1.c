#include<stdio.h>

void TestFunc();
static void StaticFunc();

void TestFunc()
{
        int i = 0;

        //printf("In TestFunc\n");

        for (i=0; i<100; i++)
                StaticFunc();

}

static void StaticFunc()
{
        int i = 0;

        //printf("In StaticFunc\n");

        for (i=0; i<100000000; i++);
}

int main(void)
{
        printf("In main\n");

        TestFunc();

        return 0;
}

/*gprof usage

Step 1. Enable profiling during compilation (use -pg option)

$ gcc -pg -o TestGprof TestGprof.c

Step 2. Execute the binary so that profiling data is generated

$ ./TestGprof

If the profiling is enabled then on executing the program, file gmon.out will be generated.

$ ls
gmon.out  TestGprof  TestGprof.c


*/


/* for graphical vizualization
sudo apt install graphviz
python3 -m pip install --user gprof2dot
gprof main.out > main.gprof
python gprof2dot.py < main.gprof | dot -Tsvg -o output.svg

use some image viewer like feh to open output.svg
feh --conversion-timeout 1 output.svg
*/
