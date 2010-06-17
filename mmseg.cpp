#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

extern "C" {
#include "php.h"
#include "php_mmseg.h"
}
#include "token.h"
#include "dict.h"
#include "algor.h"

int le_mmseg_algor; 
#define PHP_MMSEG_ALGORITHM "MMSeg Algorithm"

static function_entry mmseg_functions[] = {
	PHP_FE(mmseg_load_chars, NULL)
    PHP_FE(mmseg_load_words, NULL)
    PHP_FE(mmseg_dic_add, NULL)
    PHP_FE(mmseg_algor_create, NULL)
    PHP_FE(mmseg_algor_destroy, NULL)
    PHP_FE(mmseg_next_token, NULL)
	{NULL, NULL, NULL}
};

zend_module_entry mmseg_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_MMSEG_EXTNAME,
    mmseg_functions,       /* Functions */
    PHP_MINIT(mmseg),      /* MINIT */
    NULL,                  /* MSHUTDOWN */
    NULL,                  /* RINIT */
    NULL,                  /* RSHUTDOWN */
    NULL,                  /* MINFO */
#if ZEND_MODULE_API_NO >= 20010901
    PHP_MMSEG_EXTVER,
#endif
    STANDARD_MODULE_PROPERTIES
};

extern "C" {
#ifdef COMPILE_DL_MMSEG
ZEND_GET_MODULE(mmseg)
#endif
}

PHP_MINIT_FUNCTION(mmseg) {
    le_mmseg_algor = zend_register_list_destructors_ex(NULL, NULL, PHP_MMSEG_ALGORITHM, module_number);
    return SUCCESS;
}

PHP_FUNCTION(mmseg_load_chars) {
	char *path;
	int path_len;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &path, &path_len) == FAILURE) {
		RETURN_NULL();
	}

    if (rmmseg::dict::load_chars(path)) {
		RETURN_LONG(1);
	}
	RETURN_LONG(0);
}

PHP_FUNCTION(mmseg_load_words) {
	char *path;
	int path_len;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &path, &path_len) == FAILURE) {
		RETURN_NULL();
	}

    if (rmmseg::dict::load_words(path)) {
		RETURN_LONG(1);
	}
	RETURN_LONG(0);
}

// TODO: !!
PHP_FUNCTION(mmseg_dic_add) {
    char *word;
    int len;
    int freq;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|l", &word, &len, &freq) == FAILURE) {
		RETURN_NULL();
	}

    rmmseg::Word *w = rmmseg::make_word(word, len, freq, strlen(word));
    rmmseg::dict::add(w);
}

PHP_FUNCTION(mmseg_algor_create) {
    char *text;
    int len;
    
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &text, &len) == FAILURE) {
		RETURN_NULL();
	}

    rmmseg::Algorithm *algor = new rmmseg::Algorithm(text, len);

    ZEND_REGISTER_RESOURCE(return_value, algor, le_mmseg_algor);
}

PHP_FUNCTION(mmseg_algor_destroy) {
    rmmseg::Algorithm *algor;
    zval *zalgor;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zalgor) == FAILURE) {
		RETURN_NULL();
	}

    ZEND_FETCH_RESOURCE(algor, rmmseg::Algorithm*, &zalgor, -1, PHP_MMSEG_ALGORITHM, le_mmseg_algor);
    delete algor;
}

PHP_FUNCTION(mmseg_next_token) {
    rmmseg::Algorithm *algor;
    zval *zalgor;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zalgor) == FAILURE) {
		RETURN_NULL();
	}

    ZEND_FETCH_RESOURCE(algor, rmmseg::Algorithm*, &zalgor, -1, PHP_MMSEG_ALGORITHM, le_mmseg_algor);

    rmmseg::Token rtk = algor->next_token();
    if (rtk.length <= 0) {
        RETURN_NULL();
    }

    array_init(return_value);
    add_assoc_string(return_value, "text", estrndup(rtk.text, rtk.length), 1);
    add_assoc_long(return_value, "offset", rtk.text - algor->get_text());
    add_assoc_long(return_value, "length", rtk.length);
}

