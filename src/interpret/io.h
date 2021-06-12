#ifndef __IO_H__
#define __IO_H__

#ifndef __cplusplus //C

#define file(type) struct {  \
  file_descriptor desc;      \
  type record;               \
}

typedef text_descriptor text;

extern text input, output;

#define VOID_FILE     {{0}}

#define rewrite(file_variable, file_name, options, error_code)  \
        pio_rewrite_file(&(file_variable).desc, \
             sizeof((file_variable).record), \
             file_name, options, error_code)

#define reset(file_variable, file_name, options, error_code) \
        pio_reset_file(&(file_variable).desc, \
               sizeof((file_variable).record), \
               file_name, options, error_code)

#define get(file_variable) \
        pio_get_record(&(file_variable).desc, (void*)&(file_variable).record, \
               sizeof((file_variable).record))

#define put(file_variable) \
        pio_put_record(&(file_variable).desc, (void*)&(file_variable).record, \
               sizeof((file_variable).record))

#define sread(file_variable, value)  \
        pio_read_record(&(file_variable).desc, (void*)&(file_variable).record,\
            sizeof((file_variable).record), (void*)&(value))

#define scopy(src_file, dst_file)  \
        pio_copy_record(&(src_file).desc, (void*)&(src_file).record,\
            &(dst_file).desc, (void*)&(dst_file).record,\
            sizeof((src_file).record))

#define swrite(file_variable, value) \
        pio_write_record(&(file_variable).desc,(void*)&(file_variable).record,\
             sizeof((file_variable).record), (void*)&(value))

#define currec(file_variable) \
        (pio_access_record(&(file_variable).desc, \
               (void*)&(file_variable).record, \
               sizeof((file_variable).record)), \
     &(file_variable).record)

#define store(file_variable, value) \
        pio_store_record(&(file_variable).desc, \
             (void*)&(file_variable).record, \
             sizeof((file_variable).record), (void*)&(value))

#define eof(file_variable) \
        pio_check_end_of_file(&(file_variable).desc)

#define iostatus(file_variable) \
        pio_iostatus(&(file_variable).desc)

#define ioerror(file_variable) \
        pio_ioerror(&(file_variable).desc)


#define close(file_variable) \
        pio_close_file(&(file_variable).desc)

#define seek(file_variable, position) \
        pio_seek_file(&(file_variable).desc, (void*)&(file_variable).record, \
              sizeof((file_variable).record), position)

#define rename(file_variable, new_name) \
        pio_rename_file(&(file_variable).desc, new_name)

#define flush(file_variable) \
        pio_flush_file(&(file_variable).desc)

#define Delete(file_variable) \
        pio_delete_file(&(file_variable).desc)

#define noioerror(file_variable) \
        pio_file_ignore_error(&(file_variable).desc)

#define file_is_opened(file_variable)  ((file_variable).desc.f != NULL)

#define page(text_variable) \
        pio_output_end_of_page(&text_variable)

#define eoln(text_variable) \
        pio_check_end_of_line(&text_variable)


void tread(text* text_file, char* format_string, ...);

void twrite(text* text_file, char* format_string, ...);

void cread(char* format_string, ...);

void cwrite(char* format_string, ...);

#endif

/*
 * Codes returned by Sun Pascal open()
 */
enum open_file_errors1 {
   file_successfully_opened = 0,
   file_not_specified       = 1,
   unable_to_open_file      = 2,
   invalid_history          = 3,
   file_already_exists      = 4
};

#endif


