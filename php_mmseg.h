#ifndef PHP_MMSEG_H
#define PHP_MMSEG_H 1

#define PHP_MMSEG_EXTVER "0.1"
#define PHP_MMSEG_EXTNAME "mmseg"

PHP_MINIT_FUNCTION(mmseg); 

PHP_FUNCTION(mmseg_load_chars);
PHP_FUNCTION(mmseg_load_words);
PHP_FUNCTION(mmseg_dic_add);
PHP_FUNCTION(mmseg_algor_create);
PHP_FUNCTION(mmseg_algor_destroy);
PHP_FUNCTION(mmseg_next_token);

extern zend_module_entry mmseg_module_entry;
#define phpext_mmseg_ptr &mmseg_module_entry

#endif /* PHP_MMSEG_H */
