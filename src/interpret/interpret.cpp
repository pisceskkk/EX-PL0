#include "ptoc.h"


const integer stacksize = 1023;
const integer cxmax = 200;
const integer levmax = 10;
const integer amax = 2047;
enum types {notyp, ints, chars, arrays, reals, recds, last_types}; /* real, recds. sk*/
enum opcod {lit, lod, ilod, loda, lodt, sto, lodb, cpyb, jmp, jpc, red, wrt,
            cal, retp, endp, udis, opac, entp, ands, ors, nots, imod, mus, add,
            sub, mult, idiv, eq, ne, ls, le, gt, ge,
            radd, rsub, rmult, rdiv, rls, rle, rgt, rge, /* real. sk*/
            last_opcod
           };  /* opration code */
struct instruction
{
    opcod f;
    unsigned char l;
    unsigned int a;
};
integer pc, base, top; /* program-,base-,topstack-register */
integer oldtop;
instruction i;          /* instruction register */

array<0, stacksize, integer> s;                     /* data store */

array<0, levmax, integer> display;
array<0, cxmax, instruction> code;
file<instruction> fcode;
string filecode;            /* name of code file */
boolean stop;
integer h1, h2, h3;
char ch;
float num_real;
void load()
{
    integer i;

    output << "please input code file:" << NL;
    input >> filecode;
    assign(fcode, filecode);
    reset(fcode);
    i = 0;
    while (! eof(fcode))
    {
        fcode >> code[i];
        i = i + 1;
    }
    close(fcode);
}
int encode(float f){ /* real. sk*/
    int sign = 1;
    if(f < 0)sign = -1, f= -f;
    return sign*(*((int *)&f));
}

float decode(int i){ /* real. sk*/
    int sign = 1;
    if(i < 0)sign = -1, i= -i;
    return sign*(*((float *)&i));
}

int main(int argc, const char *argv[])
{
    /* main */
    pio_initialize(argc, argv);
    load();
    output << "START PL/0" << NL;
    oldtop = 0;
    stop = false;
    top = 0;
    base = 0;
    pc = 0;
    display[1] = 0;
    s[1] = 0;
    s[2] = 0;
    s[3] = 0;
    do
    {
        i = code[pc];
        pc = pc + 1;
        switch (i.f)
        {
        case lit:
        {
            top = top + 1;
            s[top] = i.a;
        }
        break;
        case lod:
        {
            top = top + 1;
            s[top] = s[display[i.l] + i.a];
        }
        break;
        case loda:
        {
            top = top + 1;
            s[top] = display[i.l] + i.a;
        }
        break;
        case ilod:
        {
            top = top + 1;
            s[top] = s[s[display[i.l] + i.a]];
        }
        break;
        case lodt:
        {
            s[top] = s[s[top]];
        }
        break;
        case lodb:
        {
            h1 = s[top];
            top = top - 1;
            h2 = i.a + top;
            while (top < h2)
            {
                top = top + 1;
                s[top] = s[h1];
                h1 = h1 + 1;
            }
        }
        break;
        case cpyb:
        {
            h1 = s[top - 1];
            h2 = s[top];
            h3 = h1 + i.a;
            while (h1 < h3)
            {
                s[h1] = s[h2];
                h1 = h1 + 1;
                h2 = h2 + 1;
            }
            top = top - 2;
        }
        break;
        case sto:
        {
            s[s[top - 1]] = s[top];
            top = top - 2;
        }
        break;
        case opac:
        {
            oldtop = top;
            top = top + 3;
        }
        break;
        case cal:    /* generate new block mark */
        {
            s[oldtop + 1] = pc;
            s[oldtop + 2] = display[i.l];
            s[oldtop + 3] = base;
            pc = i.a;
        }
        break;
        case entp:
        {
            base = oldtop + 1;
            display[i.l] = base;
            top = oldtop + i.a;
        }
        break;
        case udis:
        {
            h1 = i.a;
            h2 = i.l;
            h3 = base;
            do
            {
                display[h1] = h3;
                h1 = h1 - 1;
                h3 = s[h3 + 2];
            }
            while (!(h1 == h2));
        }
        break;
        case jmp:
            pc = i.a;
            break;
        case jpc:
        {
            if (s[top] == 0)  pc = i.a;
            top = top - 1;
        }
        break;
        case retp:  /*return*/
        {
            top = base - 1;
            pc = s[top + 1];
            base = s[top + 3];
        }
        break;
        case endp:
        {
            stop = true;
        }
        break;
        case red:
        {
            output << " ??:";
            if (i.a == 0)  input >> s[s[top]] >> NL;
            else if (i.a == 1)
            {
                input >> ch >> NL;
                s[s[top]] = ch;
            }
            else if (i.a == 2) /* real. sk*/
            {
                input >> num_real >> NL;
                s[s[top]] = encode(num_real);
            }
            top = top - 1;
        }
        break;
        case wrt:
        {
            if (i.a == 0)  output << s[top] << NL;
            else if(i.a == 1)
            {
                ch = s[top];
                output << ch << NL;
            }
            else if(i.a == 2) /* real. sk*/
            {
                output << decode(s[top]) << NL;
            }
            top = top - 1;
        }
        break;
        case mus :
            s[top] = -s[top];
            break;
        case add :
        {
            top = top - 1;
            s[top] = s[top] + s[top + 1];
        }
        break;
        case sub :
        {
            top = top - 1;
            s[top] = s[top] - s[top + 1];
        }
        break;
        case mult:
        {
            top = top - 1;
            s[top] = s[top] * s[top + 1];
        }
        break;
        case idiv:
        {
            top = top - 1;
            s[top] = s[top] / s[top + 1];
        }
        break;
        case imod:
        {
            top = top - 1;
            s[top] = s[top] % s[top + 1];
        }
        break;
        case ands:
        {
            top = top - 1;
            s[top] = s[top] & s[top + 1];
        }
        break;
        case ors :
        {
            top = top - 1;
            s[top] = s[top] |  s[top + 1];
        }
        break;
        case nots:
            s[top] = ~ s[top];
            break;
        case eq  :
        {
            top = top - 1;
            s[top] = (s[top] == s[top + 1]);
        }
        break;
        case ne  :
        {
            top = top - 1;
            s[top] = (s[top] != s[top + 1]);
        }
        break;
        case ls  :
        {
            top = top - 1;
            s[top] = (s[top] < s[top + 1]);
        }
        break;
        case ge  :
        {
            top = top - 1;
            s[top] = (s[top] >= s[top + 1]);
        }
        break;
        case gt  :
        {
            top = top - 1;
            s[top] = (s[top] > s[top + 1]);
        }
        break;
        case le  :
        {
            top = top - 1;
            s[top] = (s[top] <= s[top + 1]);
        }
        break;
        case radd : /* real. sk*/
        {
            top = top - 1;
            s[top] = encode(decode(s[top]) + decode(s[top + 1]));
        }
        break;
        case rsub :
        {
            top = top - 1;
            s[top] = encode(decode(s[top]) - decode(s[top + 1]));
        }
        break;
        case rmult:
        {
            top = top - 1;
            s[top] = encode(decode(s[top]) * decode(s[top + 1]));
        }
        break;
        case rdiv:
        {
            top = top - 1;
            printf("%f %f %f %d\n", decode(s[top]), decode(s[top + 1]),decode(s[top]) / decode(s[top + 1]), encode(decode(s[top]) / decode(s[top + 1])) );
            s[top] = encode(decode(s[top]) / decode(s[top + 1]));
        }
        break;
        case rls  :
        {
            top = top - 1;
            s[top] = (decode(s[top]) < decode(s[top + 1]));
        }
        break;
        case rge  :
        {
            top = top - 1;
            s[top] = (decode(s[top]) >= decode(s[top + 1]));
        }
        break;
        case rgt  :
        {
            top = top - 1;
            s[top] = (decode(s[top]) > decode(s[top + 1]));
        }
        break;
        case rle  :
        {
            top = top - 1;
            s[top] = (decode(s[top]) <= decode(s[top + 1]));
        }
        break;
        }    /* case,with */
    }
    while (!(stop == true));
    output << " END PL/0 " << NL;
    return EXIT_SUCCESS;
}      /* interpret */
