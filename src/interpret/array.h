#ifndef __ARRAY_H__
#define __ARRAY_H__

#define BETWEEN(down, value, up) (unsigned(value) - down <= unsigned(up - down))
#define noconst
#ifdef __cplusplus
template<int low_bound, int high_bound, class Type>
class array
{
public:
    Type buf[high_bound - low_bound + 1];

    enum array_bounds
    {
        low = low_bound,
        high = high_bound
    };
    int size() const
    {
        return high_bound - low_bound + 1;
    }

    Type &operator[](int index)
    {
        assert(BETWEEN(low_bound, index, high_bound));
        return buf[index - low_bound];
    }
    Type operator[](int index) const
    {
        assert(BETWEEN(low_bound, index, high_bound));
        return buf[index - low_bound];
    }

    Type       *body()
    {
        return buf;
    }
    Type const *body() const
    {
        return buf;
    }

    Type &operator*()
    {
        return *buf;
    }


    int compare( const Type *ptr) const
    {
        return memcmp(buf, ptr, sizeof(buf));
    }

    boolean operator >  (const array &arr) const
    {
        return compare(arr.buf) > 0;
    }
    boolean operator >= (const array &arr) const
    {
        return compare(arr.buf) >= 0;
    }
    boolean operator <  (const array &arr) const
    {
        return compare(arr.buf) < 0;
    }
    boolean operator <= (const array &arr) const
    {
        return compare(arr.buf) <= 0;
    }
    boolean operator == (const array &arr) const
    {
        return compare(arr.buf) == 0;
    }
    boolean operator != (const array &arr) const
    {
        return compare(arr.buf) != 0;
    }

    boolean operator >  (const Type *ptr) const
    {
        return compare(ptr) > 0;
    }
    boolean operator >= (const Type *ptr) const
    {
        return compare(ptr) >= 0;
    }
    boolean operator <  (const Type *ptr) const
    {
        return compare(ptr) < 0;
    }
    boolean operator <= (const Type *ptr) const
    {
        return compare(ptr) <= 0;
    }
    boolean operator == (const Type *ptr) const
    {
        return compare(ptr) == 0;
    }
    boolean operator != (const Type *ptr) const
    {
        return compare(ptr) != 0;
    }

    boolean operator >  (Type elem) const
    {
        return compare(&elem) > 0;
    }
    boolean operator >= (Type elem) const
    {
        return compare(&elem) >= 0;
    }
    boolean operator <  (Type elem) const
    {
        return compare(&elem) < 0;
    }
    boolean operator <= (Type elem) const
    {
        return compare(&elem) <= 0;
    }
    boolean operator == (Type elem) const
    {
        return compare(&elem) == 0;
    }
    boolean operator != (Type elem) const
    {
        return compare(&elem) != 0;
    }

    friend text &operator << (text &t, array a)
    {
        pio_output_string((text_descriptor *)&t, (char *)a.buf,
                          high_bound - low_bound + 1, NULL);
        return t;
    }

    friend text &operator >> (text &t, array &a)
    {
        pio_input_string((text_descriptor *)&t, (char *)a.buf,
                         high_bound - low_bound + 1, true);
        return t;
    }

    friend format_string < high_bound - low_bound + 1 > format(array const &a,
            int width)
    {
        return format_string < high_bound - low_bound + 1 > ((char *)a.buf, width);
    }


    void assign(array const &a)
    {
        memcpy(buf, a.buf, sizeof(buf));
    }
    void assign(const Type *ptr)
    {
        if (sizeof(Type) == 1)   /* array of char */
        {
            size_t len = strlen((char *)ptr);
            if (len > sizeof(buf))
            {
                memcpy(buf, ptr, sizeof(buf));
            }
            else
            {
                memcpy(buf, ptr, len);
                if (len < sizeof(buf))
                {
                    memset(buf + len, ' ', sizeof(buf) - len);
                }
            }
        }
        else
        {
            memcpy(buf, ptr, sizeof(buf));
        }
    }
    void assign(Type elem)
    {
        buf[0] = elem;
        if (sizeof(Type) == 1 && sizeof(buf) > 1)
        {
            memset(buf + 1, ' ', sizeof(buf) - 1);
        }
    }


    /* constructor of array from string */
    static array make(Type const *ptr)
    {
        array a;
        if (sizeof(Type) == 1)   /* array of char */
        {
            size_t len = strlen((char *)ptr);
            if (len > sizeof(a.buf))
            {
                memcpy(a.buf, ptr, sizeof(a.buf));
            }
            else
            {
                memcpy(a.buf, ptr, len);
                if (len < sizeof(a.buf))
                {
                    memset(a.buf + len, ' ', sizeof(a.buf) - len);
                }
            }
        }
        else
        {
            memcpy(a.buf, ptr, sizeof(a.buf));
        }
        return a;
    }

};

#endif/*CPP*/
#endif/*ARRAY_H*/
