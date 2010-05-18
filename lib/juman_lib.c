/*
==============================================================================
	juman_lib.c
==============================================================================
*/
 
/*
  Ϣ��ɽ�˴�Ť�����Ū������ۤ�������ˤĤ��ơ����르�ꥺ����ñ����
  �����롥

  ��Ϣ�������

  m_buffer �ڤ� p_buffer �ι�¤�ϡ������� juman �Ȳ����Ѥ��ʤ������
  ���ơ����ߤΥ�ƥ��������Τ褦�ʾ��֤Ǥ���Ȥ��롥

  ȯɽ �� ����
  (T)     (T)

  Ϣ��֤��Ȥˤʤ�פ��ɲä�����硤�쵤�� 3�Ĥ� m_buffer �� 3�Ĥ� 
  p_buffer��������������롥

  ȯɽ �� ���� �� ���� �� �� �� �ʤ�
   (T)     (T)     (F)   (F)     (T)
                ^^^^^^^^^^^^^^^^^^^^ ����ɲ�

  â����p_buffer �ι�¤�Τ� connect �Ȥ������Ф��ɲä���Ƥ��롥(��
  �ޤˤ����� (T) �� connect = TRUE��(F) �� connect = FALSE ��ɽ���Ƥ�
  ��)����ϡ�Ϣ���������̤η����ǤؤΤĤʤ��꤬��������Τ��ɤ�����
  �Ǥ��롥����Ū�ˤϡ�Ϣ����η����ǤΤ������Ǹ�η����Ǥ��б�������ʬ
  �ʳ��� p_buffer�� connect �� FALSE �Ȥ��롥����ˤ�äơ����Τ褦��
  ��ƥ�����������ػߤǤ��롥

  ȯɽ �� ���� �� ���� �� �� �� �ʤ�
                       ��
                          �ˤ� �� ....  (Ϣ����ؤγ�����)

  ��Ʃ�������

  ��̤����ʤɤ��褿��硤�������η����Ǥ�Ϣ��°����Ʃ�ᤵ���������
  (��) �ؤҤȤ��ȡ٤ǡġġ�   �Ȥ���ʸ�����Ϥ��줿���
  �ޤ������Τ褦�ʥ�ƥ��������������

  �ҤȤ��ȡ���  ��(con_tbl �ϳ���ĤΤ��)
            ��
      ����

  ����ľ��� through_word ���ƤФ졤������ 2�Ĥ� m_buffer �� 2�Ĥ� 
  p_buffer ��������������롥�����������줿 m_buffer�ϡ�con_tbl ������
  �ۤʤäƤ��ơ�����¾�ϥ��ꥸ�ʥ������Ʊ���Ǥ��롥

  �ҤȤ��ȡ���  ��(�֤ҤȤ��ȡפ�Ʊ�� con_tbl)
            ��
                ��(con_tbl �ϳ���ĤΤ��)
            �� 
      ���ȡ���  ��(�֤��ȡפ�Ʊ�� con_tbl)

  �ʾ�Τ褦�ˡ��͡���Ϣ��°��(con_tbl)����ä� m_buffer �ڤ� p_buffer 
  ���������뤳�Ȥˤ�äơ�Ʃ�������¸����Ƥ��롥

  (�����������ΤޤޤǤ����̤ζ���ʤɤ�³������m_buffer, p_buffer ��
  ���Ƥ��ޤ��Τǡ���ʣ�����Τ�������������Ѥ����޴����Ŭ���Ԥ�
  ���Ȥˤ�äơ���ȯ���ɤ��Ǥ��롥)

  �ڿ��������

  �����ľ��˿��줬�褿���ˡ�����2�Ĥ�Ϣ�뤷�������ʷ����Ǥ��ɲä��롥

  ���� �� �� �� ��

  ���μ��˿���֣��פ��褿��硤�ޤ����Τ褦�ʥ�ƥ�������������롥

  ���� �� �� �� �� �� ��

  ����ľ��� suusi_word ���ƤФ졤�����˿���֣����פ��ɲä���롥

  ���� �� �� �� �� �� ��
             ��
                ����

  �����������Ρ֣����פη����ǥ����Ȥϸ��Ρ֣��פ����η����ǥ����Ȥ�
  ���ԡ�����롥
  */

/*
------------------------------------------------------------------------------
	inclusion of header files
------------------------------------------------------------------------------ */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#define JUMAN_LIB
#include	<juman.h>
#include	<juman_lib.h>
#include	<const.h>

#include <assert.h>

/*
------------------------------------------------------------------------------
	definition of macros
------------------------------------------------------------------------------
*/

#define         DEF_CLASS_C             "�ʻ쥳����"
#define         DEF_RENSETSU_W          "Ϣ�ܥ����ȽŤ�"
#define         DEF_KEITAISO_W          "�����ǥ����ȽŤ�"
#define         DEF_COST_HABA           "��������"
#define         DEF_DIC_FILE            "����ե�����"
#define         DEF_GRAM_FILE           "ʸˡ�ե�����"

#define 	DEF_SUUSI_HINSI		"̾��"
#define 	DEF_SUUSI_BUNRUI	"����"
#define 	DEF_KAKKO_HINSI		"�ü�"
#define 	DEF_KAKKO_BUNRUI1	"��̻�"
#define 	DEF_KAKKO_BUNRUI2	"��̽�"
#define 	DEF_KUUHAKU_HINSI	"�ü�"
#define 	DEF_KUUHAKU_BUNRUI	"����"

#define 	DEF_UNDEF		"̤�����"
#define 	DEF_UNDEF_KATA		"��������"
#define 	DEF_UNDEF_ALPH		"����ե��٥å�"
#define 	DEF_UNDEF_ETC		"����¾"

/*
------------------------------------------------------------------------------
	GLOBAL:
	definition of global variables          >>> changed by T.Nakamura <<<
------------------------------------------------------------------------------
*/

char			*ProgName = NULL;
/*FILE			*db = NULL;*/
extern CLASS		Class[CLASSIFY_NO + 1][CLASSIFY_NO + 1];
extern TYPE		Type[TYPE_NO];
extern FORM		Form[TYPE_NO][FORM_NO];
extern RENSETU_PAIR     *rensetu_tbl;
extern U_CHAR           *rensetu_mtr;

DIC_FILES               DicFile;

extern FILE		*Jumanrc_Fileptr;
int              	LineNo;
int     		LineNoForError;       /* k.n */

/*
------------------------------------------------------------------------------
	LOCAL:
	definition of global variables          >>> changed by T.Nakamura <<<
------------------------------------------------------------------------------
*/
JOPTIONS JOpt;

/* ���������Ƥ�������Ǥ򸡺����뤿����Ѥ��� */
/* Ⱦ����������μ�ưǧ���Τߤ��Ѥ��� */
/* ������ܤ�ʿ��̾��³���������ܤ��б������Ҳ�̾�Ǥ���ɬ�פ��� */
const U_CHAR          *dakuon[] = {"��", "��", "��", "��", "��", "��", "��", "��", "��", "��",
			     "��", "��", "��", "��", "��", "��", "��", "��", "��", "��",
			     "��", "��", "��", "��", "��", "��", "��", "��", "��", "��",
			     "��", "��", "��", "��", "��", "��", "��", "��", "��", "��",
			     "��", "��", "��", "��", "��", "��", "��", "��", "��", "��",
			     "\0"};
const U_CHAR          *seion[]  = {"��", "��", "��", "��", "��", "��", "��", "��", "��", "��",
			     "��", "��", "��", "��", "��", "��", "��", "��", "��", "��",
			     "��", "��", "��", "��", "��", "��", "��", "��", "��", "��",
			     "��", "��", "��", "��", "��", "��", "��", "��", "��", "��",
			     "��", "��", "��", "��", "��", "��", "��", "��", "��", "��",
			     "\0"};	     
const U_CHAR *lowercase[] = {"��", "��", "��", "��", "��", "��", "��",
		       "��", "��", "��", "��", "��", "��",
		       "��", "��", "��", "��", "��", "��", "��", "��", "\0"};
const U_CHAR *uppercase[] = {"��", "��", "��", "��", "��", "��", "��",
		       "��", "��", "��", "��", "��", "��", "\0"};
const int normalized_lowercase = 7; /* ����������lowercase[]���ϰ�(7��"��"�ޤǤ��о�) */

char		Jumangram_Dirname[FILENAME_MAX];  /*k.n*/

/*
------------------------------------------------------------------------------
	prototype definition of functions       >>> changed by T.Nakamura <<<
------------------------------------------------------------------------------
*/

static BOOL katuyou_process(JCONTEXT* ctx, int position, int *k,
                            MRPH mrph, int *length, int normal_flag);

/*
------------------------------------------------------------------------------
	PROCEDURE: <changeDictionary>          >>> changed by T.Nakamura <<<
------------------------------------------------------------------------------
*/

void changeDictionary(JCONTEXT *ctx, int number)
{
  ctx->dicFile_now = number;
}

/*
------------------------------------------------------------------------------
	PROCEDURE: <juman_init_rc>
------------------------------------------------------------------------------
*/

BOOL juman_init_rc(FILE *fp)
{
    int  num, win32_decided = 0;
    char dic_file_name[BUFSIZE], full_file_name[BUFSIZE];
    CELL *cell1, *cell2;
    
    LineNo = 0 ;
    
    /* DEFAULT VALUE*/
    
    JOpt.cost_omomi.keitaiso = KEITAISO_WEIGHT_DEFAULT;
    JOpt.cost_omomi.rensetsu = RENSETSU_WEIGHT_DEFAULT * MRPH_DEFAULT_WEIGHT;
    JOpt.cost_omomi.cost_haba = COST_WIDTH_DEFAULT * MRPH_DEFAULT_WEIGHT;
    
    /* 
     *  MS Windows �ϼ���Υѥ���,juman.ini ����������� (����Dir ��1�ĤΤ� (����ȴ))
     *  ������ gramfile == dicfile
     *  Changed by Taku Kudoh (taku@pine.kuee.kyoto-u.ac.jp)
     */
#ifdef _WIN32
    /* ʸˡ�ե����� */
    num = 0;
    GetPrivateProfileString("juman","dicfile","",Jumangram_Dirname,sizeof(Jumangram_Dirname),"juman.ini");
    if (Jumangram_Dirname[0]) {
	grammar(NULL);
	katuyou(NULL);
	connect_table(NULL);
	connect_matrix(NULL);

	/* ����ե����� */
	GetPrivateProfileString("juman","dicfile","",dic_file_name,sizeof(dic_file_name),"juman.ini");
	if ((endchar(dic_file_name)) != '\\')
	    strcat(dic_file_name, "\\");

        build_full_filename(dic_file_name, PATFILE, full_file_name);
	strcat(dic_file_name, DICFILE);
	DicFile.dic[num] = my_open_entry(dic_file_name);
	pat_init_tree_top(&DicFile.tree_top[0]);
	com_l(full_file_name, &DicFile.tree_top[0]);
	DicFile.number = 1;
	/*changeDictionary(0); -> ctx */
	win32_decided = 1;
    }
    /* juman.ini�����ѤǤ��ʤ���С�jumanrc�����ɤ� */
#endif
    
    while (!s_feof(fp)) { 
	LineNoForError = LineNo ;
	cell1 = s_read(fp);

	/* ʸˡ�ե����� */
	if (!win32_decided && !strcmp(DEF_GRAM_FILE, _Atom(car(cell1)))) {
	    if (!Atomp(cell2 = car(cdr(cell1)))) {
		return FALSE;
	    } else {
		strcpy(Jumangram_Dirname , _Atom(cell2));
		grammar(NULL);
		katuyou(NULL);
		connect_table(NULL);
		connect_matrix(NULL);
	    }
	}
	  
	/* ����ե����� */
	else if (!win32_decided && !strcmp(DEF_DIC_FILE, _Atom(car(cell1)))) {
	    cell2 = cdr(cell1) ;
	    for(num = 0 ; ; num++) {
		if( Null(car(cell2)) )  break;
		else if ( !Atomp( car(cell2) ) ) {
		    return FALSE;
		}
		else if(num >= MAX_DIC_NUMBER)
		    error(ConfigError, "Too many dictionary files.", EOA);
		else {
		    strcpy(dic_file_name, _Atom(car(cell2)));
		    if ((endchar(dic_file_name)) != '/')
			strcat(dic_file_name, "/");
		    cell2 = cdr(cell2);
		      
		    /* ����Υ����ץ� */
                    build_full_filename(dic_file_name, PATFILE,
                                        full_file_name);
		    strcat(dic_file_name, DICFILE);
		    DicFile.dic[num] = my_open_entry(dic_file_name);
		    pat_init_tree_top(&DicFile.tree_top[num]);
		    com_l(full_file_name, &DicFile.tree_top[num]);
		}
	    }
	    DicFile.number = num;
	    /*changeDictionary(0); -> ctx */
	}
	/* Ϣ�ܥ����ȽŤ� */
	else if (!strcmp(DEF_RENSETSU_W, _Atom(car(cell1)))) { 
	    if (!Atomp(cell2 = car(cdr(cell1)))) {
		return FALSE;
	    } else 
		JOpt.cost_omomi.rensetsu = 
		    (int) atoi(_Atom(cell2)) * MRPH_DEFAULT_WEIGHT;
	}
	  
	/* �����ǥ����ȽŤ� */
	else if (!strcmp(DEF_KEITAISO_W, _Atom(car(cell1)))) { 
	    if (!Atomp(cell2 = car(cdr(cell1)))) {
		return FALSE;
	    } else 
		JOpt.cost_omomi.keitaiso = (int) atoi(_Atom(cell2));
	}
	  
	/* �������� */
	else if (!strcmp(DEF_COST_HABA, _Atom(car(cell1)))) { 
	    if (!Atomp(cell2 = car(cdr(cell1)))) {
		return FALSE;
	    } else 
		JOpt.cost_omomi.cost_haba = 
		    (int) atoi(_Atom(cell2)) * MRPH_DEFAULT_WEIGHT;
	}
	  
	/* �ʻ쥳����*/
	else if (!strcmp(DEF_CLASS_C, _Atom(car(cell1)))) { 
	    read_class_cost(cdr(cell1));
	}

	/* ̤����쥳���� (3.4�ʹ�����)
	else if (!strcmp("̤������ʻ�", _Atom(car(cell1))));
	*/
    }
    return TRUE;
}

/* juman_init_rc with a filename (allows not to pass FILE* among potentially
   different C libraries within different DLL's) */
BOOL juman_init_rc_file(const char *filename)
{
  FILE *fp = my_fopen_silent(filename, "rb");
  if (fp != NULL) {
    BOOL ret = juman_init_rc(fp);
    fclose(fp);
    return ret;
  }
  return FALSE;
}

/* cross-DLL symbol problems */
JOPTIONS *juman_get_options(void)
{
  return &JOpt;
}


/*
------------------------------------------------------------------------------
        PROCEDURE: <juman_close>             >>> changed by T.Nakamura <<<
------------------------------------------------------------------------------
*/
BOOL juman_close(void)
{
  int i;

  for(i = 0 ; i < DicFile.number ; i++)
    my_close_entry(DicFile.dic[i]);

  my_free(rensetu_tbl);
  my_free(rensetu_mtr);

  return TRUE;
}

/*
------------------------------------------------------------------------------
        PROCEDURE: <realloc_mrph_buffer>
------------------------------------------------------------------------------
*/
void	realloc_mrph_buffer(JCONTEXT* ctx)
{
    ctx->mrph_buffer_max += BUFFER_BLOCK_SIZE;
    ctx->m_buffer = (MRPH *)my_realloc(ctx->m_buffer, sizeof(MRPH)*ctx->mrph_buffer_max);
    ctx->m_check_buffer = (int *)my_realloc(ctx->m_check_buffer,
				       sizeof(int)*ctx->mrph_buffer_max);
}

/*
------------------------------------------------------------------------------
        PROCEDURE: <realloc_process_buffer>
------------------------------------------------------------------------------
*/
void	realloc_process_buffer(JCONTEXT* ctx)
{
    ctx->process_buffer_max += BUFFER_BLOCK_SIZE;
    ctx->p_buffer = (PROCESS_BUFFER *)my_realloc(ctx->p_buffer,
				    sizeof(PROCESS_BUFFER)*(ctx->process_buffer_max));
    ctx->path_buffer = (int *)my_realloc(ctx->path_buffer,
				       sizeof(int)*ctx->process_buffer_max);
    ctx->match_pbuf = (int *)my_realloc(ctx->match_pbuf, 
				       sizeof(int)*ctx->process_buffer_max);
}

/*
------------------------------------------------------------------------------
        PROCEDURE: <read_class_cost>
------------------------------------------------------------------------------
*/
void read_class_cost(CELL *cell)
{
    /* �ʻ쥳���Ȥ��ɤ߹��� (���������ͥ��) */

    CELL *pos_cell;
    int hinsi, bunrui, cost;

    while (!Null(car(cell))) {

	pos_cell = car(car(cell)) ;
	cost = (int) atoi(_Atom(car(cdr(car(cell)))));

	if (!strcmp(_Atom(car(pos_cell)), "*")) {
	    /* �ʻ줬 * �ʤ����Τ� */
	    for (hinsi = 1 ; Class[hinsi][0].id; hinsi++)
		for (bunrui = 0 ; Class[hinsi][bunrui].id ; bunrui++)
		    Class[hinsi][bunrui].cost = cost;
	}
	else {
	    hinsi = get_hinsi_id(_Atom(car(pos_cell)));
	    if (Null(car(cdr(pos_cell))) || 
		!strcmp(_Atom(car(cdr(pos_cell))), "*")) {
		/* ��ʬ�ब * �ޤ���̵���ʤ��ʻ����Τ� */
		for (bunrui = 0; Class[hinsi][bunrui].id ; bunrui++)
		    Class[hinsi][bunrui].cost = cost;
	    }
	    else {
		/* �ʻ졤��ʬ��Ȥ�˻��ꤵ�줿��� */
		bunrui = get_bunrui_id(_Atom(car(cdr(pos_cell))), hinsi);
		Class[hinsi][bunrui].cost = cost;
	    }
	}
	cell = cdr(cell);		
    }

    /* default */
  
    for (hinsi = 1; Class[hinsi][0].id; hinsi++) {
        assert(hinsi >= 0 && hinsi < CLASSIFY_NO + 1);
	for (bunrui = 0; Class[hinsi][bunrui].id; bunrui++) {
            assert(bunrui >= 0 && bunrui < CLASSIFY_NO + 1);
	    if (Class[hinsi][bunrui].cost == 0) 
		Class[hinsi][bunrui].cost = CLASS_COST_DEFAULT;
        }
    }
    
    /* For ʸƬ ʸ�� added by S.Kurohashi */

    Class[0][0].cost = 0;
}

/*
------------------------------------------------------------------------------
	PROCEDURE: <katuyou_process>       >>> changed by T.Nakamura <<<
------------------------------------------------------------------------------
*/
static BOOL katuyou_process(JCONTEXT* ctx, int position, int *k, MRPH mrph, int *length, int normal_flag)
{
     assert(mrph.katuyou1 >= 0);
     assert(*k >= 0 && *k < FORM_NO);
     while (Form[mrph.katuyou1][*k].name) {
          assert(mrph.katuyou1 >= 0);
          assert(*k >=0 && *k < FORM_NO);
	  if (compare_top_str1(Form[mrph.katuyou1][*k].gobi,
			      ctx->String + position + mrph.length) ||
	      normal_flag && /* ������ɽ���� */
	      compare_top_str1(Form[mrph.katuyou1][*k].gobi,
			       ctx->NormalizedString + position + mrph.length)) {
	       *length     = mrph.length + 
		    strlen(Form[mrph.katuyou1][*k].gobi);
	       return TRUE;
   	  } else {
	       (*k)++;
	  }
     }
     return FALSE;
}

/*
------------------------------------------------------------------------------
	PROCEDURE: <search_all>       >>> changed by T.Nakamura <<<
------------------------------------------------------------------------------
*/
int search_all(JCONTEXT* ctx, int position)
{
    MRPH        mrph;
    int         dic_no;
    int         jmp ;
    int		i;
    char	*pbuf;

    if (ctx->pat_buffer_max == 0)
      ctx->pat_buffer_max = 50000;
    if (ctx->pat_buffer == NULL)
      ctx->pat_buffer = (char*) my_alloc(ctx->pat_buffer_max);

    for(dic_no = 0 ; dic_no < DicFile.number ; dic_no++) {
        changeDictionary(ctx, dic_no);

	/* �ѥȥꥷ���ڤ�������Ǥ򸡺� */
  	ctx->pat_buffer[0] = '\0';
	pat_search(ctx->pat_search_buffer, DicFile.dic[ctx->dicFile_now],
                   ctx->String + position, &DicFile.tree_top[dic_no],
		   ctx->pat_buffer);
	pbuf = ctx->pat_buffer;
      
	while (*pbuf != '\0') {
            if (take_data(ctx, position, &pbuf, 0, 0) == FALSE) return FALSE;
	}

	/* �ѥȥꥷ���ڤ�������Ǥ򸡺�(������ɽ����) by sasano */
	if (JOpt.Normalized_Opt) {
	    if (strncmp(ctx->String + position, ctx->NormalizedString + position, NORMALIZED_LENGTH * 2)) {
		ctx->pat_buffer[0] = '\0';
		pat_search(ctx->pat_search_buffer,
                           DicFile.dic[ctx->dicFile_now],
                           ctx->NormalizedString + position,
                           &DicFile.tree_top[dic_no],
			   ctx->pat_buffer);
		pbuf = ctx->pat_buffer;
		
		while (*pbuf != '\0') {
		    if (take_data(ctx, position, &pbuf, 0, 1) == FALSE) return FALSE;
		}
	    }
	}

	if (JOpt.Vocalize_Opt) {
            U_CHAR *buf  = my_alloc(ctx->String_max);
	    /* ���������������Ǥ��б����뤿��ν��� by sasano
	       �Ȥꤢ��������������Ϥޤ�줬���ä�����
	       ���٤��б�������������Ϥޤ��⸡�����Ƥ���
	       take_data�ʲ���ľ����̾�졢�ޤ���ư���Ϣ�ѷ��Ǥ���ʤɤ����¤�
	       �������˥ڥʥ�ƥ��򤫤��Ƥ���("dakuon_flag"�Ǹ�����ǽ)
	    */
	    for (i = 10; *dakuon[i]; i++) {
		if (!strncmp(ctx->String + position, dakuon[i], 2)) {
		    sprintf(buf, "%s%s", seion[i], ctx->String + position + 2);

		    /* �ѥȥꥷ���ڤ�������Ǥ򸡺� */	
		    ctx->pat_buffer[0] = '\0';

                    pat_search(ctx->pat_search_buffer, DicFile.dic[ctx->dicFile_now], buf, &DicFile.tree_top[dic_no], ctx->pat_buffer);
		    pbuf = ctx->pat_buffer;

		    while (*pbuf != '\0') {
                      if (take_data(ctx, position, &pbuf, i, 0) == FALSE) return FALSE;
		    }
		    break;
		}
	    }
            my_free(buf);
	}
    }
    ctx->pat_buffer[0] = '\0';

    /* �Ҥ餬�ʡ��������ʤη����֤�ɽ��������θ���Ȥ��� */
    if (JOpt.Repetition_Opt) {
	int code = check_code(ctx->String, position);
	if (code == HIRAGANA || code == KATAKANA) {
	    recognize_repetition(ctx->String + position, ctx->pat_buffer, code);
	}
    }   
    pbuf = ctx->pat_buffer;
    while (*pbuf != '\0') {
	if (take_data(ctx, position, &pbuf, 0, 0) == FALSE) return FALSE;
    }

    return TRUE;
}

/*
------------------------------------------------------------------------------
        PROCEDURE: <recognize_repetition>   >>> Added by Ryohei Sasano <<<
------------------------------------------------------------------------------
*/
int recognize_repetition(char *key, char *rslt, int orig_code)
{
    int i, len, code, next_code, weight, con_tbl;
    int key_length = strlen(key); /* ������ʸ����������Ƥ��� */
    U_CHAR *buf, *midasi = NULL;
    int midasi_len = 0;

    code = orig_code;
    for (len = 2; len < 5; len++) {

	if (key_length < len * 4) return 0;
	
	/* ��ʸ������Ϥޤ��Τ��Բ� */
	for (i = 0; *lowercase[i]; i++) {
	    if (!strncmp(key, lowercase[i], 2)) return 0;
	}

	next_code = check_code(key, len * 2 - 2);

	/* ʿ��̾���Ҳ�̾��"��"�ʳ���ޤ��Τ��Բ� */
	if (next_code != CHOON && next_code != HIRAGANA
	    && next_code != KATAKANA) return 0;
	if (next_code != CHOON) {
	    if (next_code != code) return 0;
	    code = next_code;
	}

	if (!strncmp(key, key + len * 2, len * 2)) {
            if (midasi_len < len*4 + 1) {
              midasi_len = len*4 + 1;
              if (midasi == NULL) {
                midasi = my_alloc(midasi_len);
              } else {
                midasi = my_realloc(midasi, midasi_len);
              }
            }
	    strncpy(midasi, key, len * 4);
 	    midasi[len * 4] = '\0';
	    buf = midasi;	    

	    /* ����Ū�ˤϸ�������㤷�ƥڥʥ�ƥ���Ϳ���� */
	    weight = REPETITION_COST*len+0x20;

	    /* ��ʸ�������ä�����1ʸ��ʬ�ޥ��ʥ�+�ܡ��ʥ� */
	    for (i = 2; *lowercase[i]; i++) {
		if (strstr(buf, lowercase[i])) break;
	    }
	    if (*lowercase[i]) {
		if (len == 2) return 0; /* 1���η����֤��϶ػ� */		
		weight -= REPETITION_COST + LOWERCASE_BONUS;
	    }

	    /* ���������ä�����ܡ��ʥ� */
	    for (i = 0; *dakuon[i]; i++) {
		if (strstr(buf, dakuon[i])) break;
	    }
	    if (*dakuon[i]) {
		weight -= DAKUON_BONUS;
		/* ��Ƭ���������ä����Ϥ���˥ܡ��ʥ� */
		if (!strncmp(buf, dakuon[i], 2)) weight -= DAKUON_BONUS;
	    }

	    /* �������ʤ�ܡ��ʥ� */
	    if (check_code(key, 0) == KATAKANA) weight -= KATAKANA_BONUS;
    
	    con_tbl = check_table_for_undef(8, 0); /* hinsi = 8, bunrui = 0 */
	    sprintf(rslt, "%s\t%c%c%c%c%c%c%c", buf,
		    8+0x20, /* hinsi = 8 */
		    0+0x20, /* bunrui = 0 */
		    0+0x20, /* katuyou1 = 0 */
		    0+0x20, /* katuyou2 = 0 */
		    weight, /* weight */
		    con_tbl / (0x100-0x20)+0x20,
		    con_tbl % (0x100-0x20)+0x20);
	    rslt += len * 4 + 8;

	    while (*buf) {
		*(rslt++) = *buf;
		*(rslt++) = *(buf+1);
		buf += 2;
	    }
	    *(rslt++) = 0x20;
	    *(rslt++) = 10+0x20;
	    strcpy(rslt, "\"��ưǧ��\"\n");
	    return len;
	}
    }
    if (midasi != NULL) {
      my_free(midasi);
    }
}

/*
------------------------------------------------------------------------------
        PROCEDURE: <take_data>                  >>> Changed by yamaji <<<
------------------------------------------------------------------------------
*/
int take_data(JCONTEXT* ctx, int pos, char **pbuf, int dakuon_flag, int normal_flag)
{
    unsigned char    *s;
    int     i, k, f, num;
    int	    rengo_con_tbl, rengo_weight;
    MRPH    mrph;
    MRPH    *new_mrph;
    int	    length, con_tbl_bak, k2, pnum_bak;
    PROCESS_BUFFER p_buffer_bak;
    int	    new_mrph_num;

    s = *pbuf;

    k = 0 ;
	    
    while ((mrph.midasi[k++] = *(s++)) != '\t') {
      assert(k >= 0 && k < MIDASI_MAX);
    }
    assert(k-1 >= 0 && k-1 < MIDASI_MAX);
    mrph.midasi[k-1] = '\0';
    mrph.midasi2[0] = '\0';

    if (dakuon_flag) {
	strcpy(mrph.midasi2, mrph.midasi);
	strncpy(mrph.midasi, ctx->String + pos, strlen(mrph.midasi));
	mrph.midasi[strlen(mrph.midasi)] = '\0';
    }

    if (*s == 0xff) { /* Ϣ�������ä���� */

#define 	RENGO_BUFSIZE		20

	MRPH mrph_buf[RENGO_BUFSIZE];
	int add_list[FORM_NO];
	int co, pos_bak, glen, cno;
	
	pos_bak = pos;

	s = _take_data(ctx, s, &mrph, dakuon_flag, normal_flag);
	rengo_con_tbl = mrph.con_tbl;
	rengo_weight  = mrph.weight;
	num = mrph.bunrui;

	for (i = 0; i < num; i++) { /* �ޤ���Ϣ�����Τ�Хåե����ɤ߹��� */
            assert(i >= 0 && i < RENGO_BUFSIZE);
	    new_mrph = &mrph_buf[i];

	    k = 0;
	    while ((new_mrph->midasi[k++] = *(s++)) != ' ') {
              assert(k >= 0 && k < MIDASI_MAX);
            }
            assert(k-1 >= 0 && k-1 < MIDASI_MAX);
	    new_mrph->midasi[k-1] = '\0';

	    s = _take_data(ctx, s, new_mrph, dakuon_flag, normal_flag);

	    length = strlen(new_mrph->midasi);
            assert(new_mrph->hinsi >= 0);
            assert(new_mrph->bunrui >= 0);
	    if (Class[new_mrph->hinsi][new_mrph->bunrui].kt) /* ���Ѥ��� */
		if (i < num-1) { /* �����ʳ��γ��Ѹ� */
                    assert(new_mrph->katuyou1 >= 0);
                    assert(new_mrph->katuyou2 >= 0);
		    length += strlen(
			Form[new_mrph->katuyou1][new_mrph->katuyou2].gobi);
		    new_mrph->con_tbl += (new_mrph->katuyou2-1);
		}
	    new_mrph->length = length;

	    if (i < num-1) pos += length; /* ���������Ǥΰ��֤���¸ */
/*printf(".....%d/%d   %s %d\n", i, num, new_mrph->midasi, new_mrph->con_tbl);*/
	}

        assert(num-1 >= 0 && num-1 < RENGO_BUFSIZE);
	new_mrph = &mrph_buf[num-1];
        assert(new_mrph->hinsi >= 0);
        assert(new_mrph->bunrui >= 0);
	if (Class[new_mrph->hinsi][new_mrph->bunrui].kt == 0) {
	    add_list[0] = 0;
	    add_list[1] = -1;
	} else {
	    if (new_mrph->katuyou2) {
		add_list[0] = new_mrph->katuyou2;
		add_list[1] = -1;
	    } else {
		/* �����η����Ǥ����Ѥ����� */
		k2 = strlen(new_mrph->midasi) ? 1 : 2;
		co = 0;
		while (katuyou_process(ctx, pos, &k2, *new_mrph, &length, 0)) {
                    assert(co >= 0
                           && co < sizeof(add_list)/sizeof(add_list[0]));
		    add_list[co++] = k2;
		    k2++;
		}
                assert(co >= 0 && co < sizeof(add_list)/sizeof(add_list[0]));
		add_list[co] = -1;
	    }
	}

	/* ���ѷ����Ȥ�Ϣ����ɲä��Ƥ��� */
	for (co = 0; add_list[co] >= 0; co++) {
            assert(co < FORM_NO);
	    pos = pos_bak;
	    for (i = 0; i < num; i++) {
                assert(ctx->m_buffer_num < ctx->mrph_buffer_max);
                assert(i >= 0 && i < sizeof(mrph_buf)/sizeof(mrph_buf[0]));
		ctx->m_buffer[ctx->m_buffer_num] = mrph_buf[i];
		new_mrph = &ctx->m_buffer[ctx->m_buffer_num];

		if (i == 0) { /* Ϣ�����Ƭ�η����� */
		    con_tbl_bak = new_mrph->con_tbl;
/*printf("FROM %d %d\n", new_mrph->con_tbl, rengo_con_tbl);*/
		    if (rengo_con_tbl != -1) {
			if (add_list[co]) cno = add_list[co]-1; else cno = 0;
			if (check_matrix_left(rengo_con_tbl+cno) == TRUE)
			    /* Ϣ����ͭ�κ�Ϣ�ܵ�§ */
			    new_mrph->con_tbl = rengo_con_tbl+cno;
		    }
/*printf("  TO %d\n", new_mrph->con_tbl);*/
		    pnum_bak = ctx->p_buffer_num;

		    if (JOpt.Show_Opt_debug) {
			printf("\\begin{�����Ǣ�Ϣ��} %s", mrph.midasi);
			if (add_list[co])
			    printf("%s",
				   Form[mrph_buf[num-1].katuyou1][add_list[co]].gobi);
			printf("\n");
		    }
		    
		    if (check_connect(ctx, pos, ctx->m_buffer_num, dakuon_flag) == FALSE)
                      return FALSE;
		    if (ctx->p_buffer_num == pnum_bak) break;

                    assert(pnum_bak >= 0
                           && pnum_bak < ctx->process_buffer_max);
                    assert(new_mrph->hinsi >= 0);
                    assert(new_mrph->bunrui >= 0);
		    ctx->p_buffer[pnum_bak].end = pos + new_mrph->length;
		    ctx->p_buffer[pnum_bak].connect = FALSE;
		    ctx->p_buffer[pnum_bak].score = ctx->p_buffer[pnum_bak].score +
			(Class[new_mrph->hinsi][new_mrph->bunrui].cost
			 * new_mrph->weight * JOpt.cost_omomi.keitaiso 
			 * (rengo_weight-10)/10);
		    new_mrph->con_tbl = con_tbl_bak;

		    if (JOpt.Show_Opt_debug) {
			printf("----- Ϣ���� %s %d\n", new_mrph->midasi, 
			       ctx->p_buffer[pnum_bak].score);
		    }
		} else {
                    assert(ctx->p_buffer_num-1 >= 0
                           && ctx->p_buffer_num < ctx->process_buffer_max);
                    assert(ctx->p_buffer[ctx->p_buffer_num-1].mrph_p >= 0
                           && ctx->p_buffer[ctx->p_buffer_num-1].mrph_p
                           < ctx->mrph_buffer_max);
		    ctx->p_buffer[ctx->p_buffer_num].score =
			ctx->p_buffer[ctx->p_buffer_num-1].score +
			(Class[new_mrph->hinsi][new_mrph->bunrui].cost
			 * new_mrph->weight * JOpt.cost_omomi.keitaiso +
			 (check_matrix(ctx->m_buffer[ctx->p_buffer[ctx->p_buffer_num-1].mrph_p].con_tbl, new_mrph->con_tbl) ? 
			  check_matrix(ctx->m_buffer[ctx->p_buffer[ctx->p_buffer_num-1].mrph_p].con_tbl, new_mrph->con_tbl) : DEFAULT_C_WEIGHT)
			 /* Ϣ�������³����³ɽ���������Ƥ��ʤ���礬����
			    ���ξ��ϡ���³�Υ����Ȥϥǥե���Ȥ��ͤȤ��롥 */
			 * JOpt.cost_omomi.rensetsu)
			 * rengo_weight/10;
                    assert(ctx->p_buffer_num < ctx->process_buffer_max);
		    ctx->p_buffer[ctx->p_buffer_num].mrph_p = ctx->m_buffer_num;
		    ctx->p_buffer[ctx->p_buffer_num].start = pos;
		    ctx->p_buffer[ctx->p_buffer_num].end = pos + new_mrph->length;
		    ctx->p_buffer[ctx->p_buffer_num].path[0] = ctx->p_buffer_num-1;
		    ctx->p_buffer[ctx->p_buffer_num].path[1] = -1;

		    if (i < num-1) { /* Ϣ��������η����� */
			ctx->p_buffer[ctx->p_buffer_num].connect = FALSE;
		    } else { /* Ϣ��������η����� */
			ctx->p_buffer[ctx->p_buffer_num].connect = TRUE;

			if (rengo_con_tbl != -1) {
			    if (add_list[co]) cno = add_list[co]-1;
			    else cno = 0;
			    if (check_matrix_right(rengo_con_tbl+cno) == TRUE)
				/* Ϣ����ͭ�α�Ϣ�ܵ�§ */
				new_mrph->con_tbl = rengo_con_tbl;
			}
			if (add_list[co]) {
			    new_mrph->katuyou2 = add_list[co];
			    new_mrph->con_tbl += (add_list[co]-1);
                            assert(new_mrph->katuyou1 >= 0);
                            assert(new_mrph->katuyou2 >= 0);
			    glen = strlen(Form[new_mrph->katuyou1]
					  [new_mrph->katuyou2].gobi);
			    new_mrph->length += glen;
			    ctx->p_buffer[ctx->p_buffer_num].end += glen;
			}
		    }
		    if (JOpt.Show_Opt_debug) {
			printf("----- Ϣ���� %s %d\n", new_mrph->midasi, 
			       ctx->p_buffer[ctx->p_buffer_num].score);
		    }

		    if (++(ctx->p_buffer_num) == ctx->process_buffer_max)
			realloc_process_buffer(ctx);
		}
		pos += new_mrph->length;

		/* fixed by kuro on 01/01/19
		   �ʲ���realloc�����if-else��������ä��Τǡ�new_mrph�ؤ�
		   ���������� segmentation fault �ȤʤäƤ��� */
		if (++(ctx->m_buffer_num) == ctx->mrph_buffer_max)
		  realloc_mrph_buffer(ctx);
	    }
	    if (JOpt.Show_Opt_debug) {
		printf("\\end{�����Ǣ�Ϣ��}\n");
	    }
	}

    } else {           /* ���̤η����Ǥ��ä���� */
      s = _take_data(ctx, s, &mrph, dakuon_flag, normal_flag);

	if ( Class[mrph.hinsi][mrph.bunrui].kt ) { /* ���Ѥ��� */
	    if ( mrph.katuyou2 == 0 ) {   /* �촴���� */
		k2 = 1;
		while (katuyou_process(ctx, pos, &k2, mrph, &length, normal_flag)) {
		    /* �������Ρ��ɤ�2���ʾ塢���ġ�length����оݤξ�ʸ����ޤ���Τߺ��� */
		    if (normal_flag &&
			(length == 2 ||
			 !strncmp(ctx->String + pos, ctx->NormalizedString + pos, length))) {
			k2++;
			continue;
		    }
                    assert(ctx->m_buffer_num < ctx->mrph_buffer_max);
		    ctx->m_buffer[ctx->m_buffer_num] = mrph;
		    ctx->m_buffer[ctx->m_buffer_num].katuyou2 = k2;
		    ctx->m_buffer[ctx->m_buffer_num].length = length;
		    ctx->m_buffer[ctx->m_buffer_num].con_tbl += (k2 - 1);
		    if (check_connect(ctx, pos, ctx->m_buffer_num, dakuon_flag) == FALSE)
                      return FALSE;
		    if (++(ctx->m_buffer_num) == ctx->mrph_buffer_max)
			realloc_mrph_buffer(ctx);
		    k2++;
		}
	    } else {                         /* �촴�ʤ� */
                assert(ctx->m_buffer_num < ctx->mrph_buffer_max);
		ctx->m_buffer[ctx->m_buffer_num] = mrph;
		ctx->m_buffer[ctx->m_buffer_num].midasi[0] = '\0';
		ctx->m_buffer[ctx->m_buffer_num].midasi2[0] = '\0';
		ctx->m_buffer[ctx->m_buffer_num].yomi[0]  = '\0';
		if (check_connect(ctx, pos, ctx->m_buffer_num, dakuon_flag) == FALSE)
                  return FALSE;
		if (++(ctx->m_buffer_num) == ctx->mrph_buffer_max)
		    realloc_mrph_buffer(ctx);
	    }
	} else {	                                 /* ���Ѥ��ʤ� */
	    if (!normal_flag ||  
		/* �������Ρ��ɤ�2���ʾ塢���ġ�length����оݤξ�ʸ����ޤ���Τߺ��� */
		strlen(mrph.midasi) > 2 && 
		strncmp(ctx->String + pos, ctx->NormalizedString + pos, strlen(mrph.midasi))) {
		
                assert(ctx->m_buffer_num < ctx->mrph_buffer_max);
                ctx->m_buffer[ctx->m_buffer_num] = mrph;
		if (check_connect(ctx, pos, ctx->m_buffer_num, dakuon_flag) == FALSE)
                  return FALSE;
		new_mrph_num = ctx->m_buffer_num;
		if (++(ctx->m_buffer_num) == ctx->mrph_buffer_max)
		    realloc_mrph_buffer(ctx);	    

#ifdef NUMERIC_P
		if (suusi_word(ctx, pos, new_mrph_num) == FALSE)
		    return FALSE;
#endif
#ifdef THROUGH_P
		if (through_word(ctx, pos, new_mrph_num) == FALSE)
		    return FALSE;
#endif
	    }
	}
    }
    *pbuf = s;
    return TRUE;
}

/*
------------------------------------------------------------------------------
        PROCEDURE: <_take_data>                 >>> added by T.Nakamura <<<
------------------------------------------------------------------------------
*/

char *_take_data(JCONTEXT* ctx, char *s, MRPH *mrph, int dakuon_flag, int normal_flag)
{
    int		i, j, k = 0;
    char	c, *rep;
    
    mrph->hinsi    = numeral_decode(&s);
    mrph->bunrui   = numeral_decode(&s);
    mrph->katuyou1 = numeral_decode(&s);
    mrph->katuyou2 = numeral_decode(&s);
    mrph->weight   = numeral_decode(&s);
    mrph->con_tbl  = numeral_decode2(&s);
    hiragana_decode(&s, mrph->yomi);
    mrph->length   = strlen(mrph->midasi);
    
    if (*s != ' ' && *s != '\n') { /* ��̣���󤢤� */
	j = numeral_decode(&s);
	for (i = 0; i < j; i++) {
          assert(k >= 0 && k < IMI_MAX);
          mrph->imis[k++] = *(s++);
        }
        assert(k >= 0 && k < IMI_MAX);
	mrph->imis[k] = '\0';
    }
    s++;
    
    if (dakuon_flag) {
	/* �饤�ޥ��ˡ§ */
	/* ��Ȥ��������ޤ����Ǥ����������ʤ� */
	/* �㳰�Ȥʤ�"�Ϥ���"�ˤϡ������ĤȤ���feature����Ϳ�����н褷�Ƥ��� */
	for (i = 10; *dakuon[i]; i++) {
	    if (strstr(mrph->midasi + 2, dakuon[i])) break;
	}
	/* �饤�ޥ��ˡ§�˳������촴�Τʤ��졢�����Ǥ�1ʸ�����ä���� */
	/* �������ν����Ϥ��ʤ�(=�礭�ʥڥʥ�ƥ���Ϳ����) */
	if (!strstr(mrph->imis, "������") && *dakuon[i] || 
	    mrph->katuyou2 || 
 	    (mrph->length == 2) && !Class[mrph->hinsi][mrph->bunrui].kt) {
	    mrph->weight = 255;
	}
	/* Ϣ�����¸�Τ� */
	/* ���Τ�����ɽɽ���κǽ��ʸ���������Ǥʤ���Τ��Բ� */
	else if ((rep = strstr(mrph->imis, "��ɽɽ��:")) &&
		 check_code(rep, 9) == KATAKANA) {
	    mrph->weight = 255;
	}
	else {
	    /* ư�� */
	    if (mrph->hinsi == 2) {
		if (!strncmp(mrph->midasi, "��", 2)) {
		    mrph->weight += VERB_GA_VOICED_COST;
		}
		else {
		    mrph->weight += VERB_VOICED_COST;
		}
	    }
	    /* ̾�� */
	    else if (mrph->hinsi == 6 && (mrph->bunrui < 3 || mrph->bunrui > 7)) {
		if (!strncmp(mrph->midasi, "��", 2)) {
		    mrph->weight += NOUN_GA_VOICED_COST;
		}
		else {
		    mrph->weight += NOUN_VOICED_COST;
		}
	    }
	    /* ���ƻ� */
	    else if (mrph->hinsi == 3) {
		mrph->weight += ADJECTIVE_VOICED_COST;
	    }
	    /* ����¾ */
	    /* ����¾���ʻ�Ǥ������ĤȤ�����̣�Ǥ�����в��ϤǤ���褦�ˤ��뤿�� */
	    /* �����줪��������"���餤"�����ꤷ�Ƥ��뤬���Ȥꤢ�����ϻ��Ѥ��� */
	    else if (strstr(mrph->imis, "������")) {
		mrph->weight += OTHER_VOICED_COST;
	    }
	    else {
		mrph->weight = 255;
	    }
	}
	
	/* �ɤߤ����������Ҳ�̾�ξ���ʿ��̾�ˤ��� */
	strncpy(mrph->yomi, dakuon[(dakuon_flag/2)*2], 2);
	
	if (k == 0) {
	    strcpy(mrph->imis, "\"������\"");
	}
	else {
	    mrph->imis[k - 1] = '\0';
	    strcat(mrph->imis, " ������\"");
	}
	k++;
    }

    /* ������������Τ˥ڥʥ�ƥ�(��ʸ�������줿ɽ����) */
    if (normal_flag) {
	mrph->weight += NORMALIZED_COST;
    }
    
    if (k == 0) strcpy(mrph->imis, NILSYMBOL);
    
    return(s);
}

int numeral_decode(char **str)
{
  unsigned char *s;

    s = *str;
    if (*s < 0xf0) {
	*str = s+1;
	return(*s-0x20);
    } else if (*s == 0xff) {
	*str = s+1;
	return(atoi(RENGO_ID));
    } else {
	*str = s+2;
	return((*s-0xf0)*(0xf0-0x20)+*(s+1)-0x20);
    }
}

int numeral_decode2(char **str)
{
    unsigned char *s;

    s = *str;
    *str = s+2;
    return((*s-0x20)*(0x100-0x20)+*(s+1)-0x20-1);
}

void hiragana_decode(char **str, char *yomi)
{
    unsigned char *s;

    s = *str;
    while (*s != 0x20) {
	if (*s < 0x80) {
	    *(yomi++) = 0xa4;
	    *(yomi++) = *s-0x21+0xa0;
	    s++;
	} else {
	    *(yomi++) = *(s++);
	    *(yomi++) = *(s++);
	}
    }
    *str = s+1;
    *yomi = '\0';
}

/*
------------------------------------------------------------------------------
  PROCEDURE: <trim_space> ���ڡ����κ�� (Ʃ�����Ƴ������Ѥ���)
------------------------------------------------------------------------------
*/
int trim_space(JCONTEXT* ctx, int pos)
{
    while (1) {
 	/* ���ѥ��ڡ��� */
        assert(pos >= 0 && pos + 1 < ctx->String_max);
	if (ctx->String[pos] == 0xa1 && ctx->String[pos+1] == 0xa1)
	  pos += 2;
	else
	  break;
    }
    return pos;
}
    
/*
------------------------------------------------------------------------------
  PROCEDURE: <undef_word> ̤��������
------------------------------------------------------------------------------
*/
    
int undef_word(JCONTEXT* ctx, int pos)
{
    int i, end, code, next_code;
    
    /* ����ˤ���ڤ����
       ʿ��̾��������Ⱦ�Ѷ��� �� ��ʸ��
       Ⱦ��(����ʳ�)���Ҳ�̾(�֡��פ�)������ե��٥å�(�֡��פ�) �� Ϣ³ */

    assert(pos >= 0 && pos < ctx->String_max);
    code = check_code(ctx->String, pos);
    if (code == HIRAGANA || code == KANJI) {
	end = (pos + 2);
    } else if (code == KUUHAKU) {
	end = (pos + 1);
    } else {
	end = pos;
	while(1) {
	    /* MIDASI_MAX��ۤ���̤�����Ϻ������ʤ� */
	    if (end - pos >= MIDASI_MAX - ((code == HANKAKU) ? 1 : 2)) break;

	    end += (code == HANKAKU) ? 1 : 2;
	    next_code = check_code(ctx->String, end);
	    if (next_code == code ||
		(code == KATAKANA && next_code == CHOON) ||
		(code == ALPH     && next_code == PRIOD)) continue;
	    else break;
	}
    }

    assert(ctx->m_buffer_num < ctx->mrph_buffer_max);
    switch (code) {
    case KUUHAKU:
	ctx->m_buffer[ctx->m_buffer_num].hinsi = JOpt.kuuhaku_hinsi;
	ctx->m_buffer[ctx->m_buffer_num].bunrui = JOpt.kuuhaku_bunrui;
	ctx->m_buffer[ctx->m_buffer_num].con_tbl = JOpt.kuuhaku_con_tbl;
	break;
    case KATAKANA:
	ctx->m_buffer[ctx->m_buffer_num].hinsi = JOpt.undef_hinsi;
	ctx->m_buffer[ctx->m_buffer_num].bunrui = JOpt.undef_kata_bunrui;
	ctx->m_buffer[ctx->m_buffer_num].con_tbl = JOpt.undef_kata_con_tbl;
	break;
    case ALPH:
	ctx->m_buffer[ctx->m_buffer_num].hinsi = JOpt.undef_hinsi;
	ctx->m_buffer[ctx->m_buffer_num].bunrui = JOpt.undef_alph_bunrui;
	ctx->m_buffer[ctx->m_buffer_num].con_tbl = JOpt.undef_alph_con_tbl;
	break;
    default:
	ctx->m_buffer[ctx->m_buffer_num].hinsi = JOpt.undef_hinsi;
	ctx->m_buffer[ctx->m_buffer_num].bunrui = JOpt.undef_etc_bunrui;
	ctx->m_buffer[ctx->m_buffer_num].con_tbl = JOpt.undef_etc_con_tbl;
	break;
    }

    ctx->m_buffer[ctx->m_buffer_num].katuyou1 = 0;
    ctx->m_buffer[ctx->m_buffer_num].katuyou2 = 0;
    ctx->m_buffer[ctx->m_buffer_num].length = end - pos;
    if (end - pos >= MIDASI_MAX) {
	juman_log_err("Too long undef_word<%s>\n", ctx->String);
	return FALSE;
    }
    if (code == KUUHAKU) {
	strcpy(ctx->m_buffer[ctx->m_buffer_num].midasi, "\\ ");
	strcpy(ctx->m_buffer[ctx->m_buffer_num].yomi, "\\ ");
    } else {
        assert(ctx->m_buffer_num < ctx->mrph_buffer_max);
	strncpy(ctx->m_buffer[ctx->m_buffer_num].midasi, ctx->String+pos, end - pos);
        assert(end - pos >= 0 && end - pos < MIDASI_MAX);
	ctx->m_buffer[ctx->m_buffer_num].midasi[end - pos] = '\0';
        assert(end - pos >= 0 && end - pos < YOMI_MAX);
	strncpy(ctx->m_buffer[ctx->m_buffer_num].yomi, ctx->String+pos, end - pos);
	ctx->m_buffer[ctx->m_buffer_num].yomi[end - pos] = '\0';
    }
    ctx->m_buffer[ctx->m_buffer_num].weight = MRPH_DEFAULT_WEIGHT;
    strcpy(ctx->m_buffer[ctx->m_buffer_num].midasi2, ctx->m_buffer[ctx->m_buffer_num].midasi);
    strcpy(ctx->m_buffer[ctx->m_buffer_num].imis, NILSYMBOL);

    if (check_connect(ctx, pos, ctx->m_buffer_num, 0) == FALSE)
      return FALSE;
    if (++(ctx->m_buffer_num) == ctx->mrph_buffer_max)
	realloc_mrph_buffer(ctx);

#ifdef THROUGH_P				/* Ⱦ�ѥ��ڡ���Ʃ�� */
    if (code == KUUHAKU) {
        return (through_word(ctx, pos, ctx->m_buffer_num-1));
    }
#endif

    return TRUE;
}

int check_code(U_CHAR *cp, int pos)
{
    int	code;
    
    if ( cp[pos] == '\0')			return 0;
    else if ( cp[pos] == KUUHAKU )		return KUUHAKU;
    else if ( cp[pos] < HANKAKU )		return HANKAKU;
    
    code = cp[pos]*256 + cp[pos+1];
    
    if ( code == PRIOD ) 			return PRIOD;
    else if ( code == CHOON ) 			return CHOON;
    else if ( code < KIGOU ) 			return KIGOU;
    else if ( code < SUJI ) 			return SUJI;
    else if ( code < ALPH )			return ALPH;
    else if ( code < HIRAGANA ) 		return HIRAGANA;
    else if ( code < KATAKANA ) 		return KATAKANA;
    else if ( code < GR ) 			return GR;
    else return KANJI;
}

/*
------------------------------------------------------------------------------
  PROCEDURE: <juman_init_etc> ̤�������������������Ʃ��������ν���
------------------------------------------------------------------------------
*/
void juman_init_etc(void)
{
    int i, flag;

    /* ̤���������ν��� */
    JOpt.undef_hinsi = get_hinsi_id(DEF_UNDEF);
    JOpt.undef_kata_bunrui = get_bunrui_id(DEF_UNDEF_KATA, JOpt.undef_hinsi);
    JOpt.undef_alph_bunrui = get_bunrui_id(DEF_UNDEF_ALPH, JOpt.undef_hinsi);
    JOpt.undef_etc_bunrui = get_bunrui_id(DEF_UNDEF_ETC, JOpt.undef_hinsi);
    JOpt.undef_kata_con_tbl = check_table_for_undef(JOpt.undef_hinsi,
                                                    JOpt.undef_kata_bunrui);
    JOpt.undef_alph_con_tbl = check_table_for_undef(JOpt.undef_hinsi,
                                                    JOpt.undef_alph_bunrui);
    JOpt.undef_etc_con_tbl = check_table_for_undef(JOpt.undef_hinsi,
                                                   JOpt.undef_etc_bunrui);

    /* ��������ν��� */
    JOpt.suusi_hinsi = get_hinsi_id(DEF_SUUSI_HINSI);
    JOpt.suusi_bunrui = get_bunrui_id(DEF_SUUSI_BUNRUI, JOpt.suusi_hinsi);

    /* Ʃ������ν��� */
    JOpt.kakko_hinsi = get_hinsi_id(DEF_KAKKO_HINSI);
    JOpt.kakko_bunrui1 = get_bunrui_id(DEF_KAKKO_BUNRUI1, JOpt.kakko_hinsi);
    JOpt.kakko_bunrui2 = get_bunrui_id(DEF_KAKKO_BUNRUI2, JOpt.kakko_hinsi);

    JOpt.kuuhaku_hinsi = get_hinsi_id(DEF_KUUHAKU_HINSI);
    JOpt.kuuhaku_bunrui = get_bunrui_id(DEF_KUUHAKU_BUNRUI,
                                        JOpt.kuuhaku_hinsi);
    JOpt.kuuhaku_con_tbl = check_table_for_undef(JOpt.kuuhaku_hinsi,
                                                 JOpt.kuuhaku_bunrui);
}

/*
------------------------------------------------------------------------------
  PROCEDURE: <suusi_word> �������
------------------------------------------------------------------------------
*/
    
int 	suusi_word(JCONTEXT* ctx, int pos , int m_num)
{
    int i, j;
    MRPH *new_mrph , *pre_mrph;

    assert(m_num >= 0 && m_num < ctx->mrph_buffer_max);
    new_mrph = &ctx->m_buffer[m_num];
    if (new_mrph->hinsi != JOpt.suusi_hinsi
        || new_mrph->bunrui != JOpt.suusi_bunrui)
        return TRUE;

    for (j = 0; (i = ctx->match_pbuf[j]) >= 0; j++) {
        assert(i < ctx->process_buffer_max);
        assert(ctx->p_buffer[i].mrph_p >= 0
               && ctx->p_buffer[i].mrph_p < ctx->mrph_buffer_max);
	pre_mrph = &ctx->m_buffer[ctx->p_buffer[i].mrph_p];
	if (pre_mrph->hinsi == JOpt.suusi_hinsi &&
	    pre_mrph->bunrui == JOpt.suusi_bunrui &&
	    check_matrix(pre_mrph->con_tbl, new_mrph->con_tbl) != 0) {

	    if (strlen(pre_mrph->midasi)+strlen(new_mrph->midasi) >= MIDASI_MAX
		|| strlen(pre_mrph->yomi)+strlen(new_mrph->yomi) >= YOMI_MAX) {
		/* MIDASI_MAX��YOMI_MAX��ۤ�������ʬ�䤹��褦���ѹ� 08/01/15 */
/* 		juman_log_err( "Too long suusi<%s>\n", ctx->String); */
/* 		return FALSE; */
		return TRUE;
	    }
            assert(ctx->m_buffer_num >= 0
                   && ctx->m_buffer_num < ctx->mrph_buffer_max);
	    ctx->m_buffer[ctx->m_buffer_num] = *pre_mrph;
	    strcat(ctx->m_buffer[ctx->m_buffer_num].midasi , new_mrph->midasi);
	    strcat(ctx->m_buffer[ctx->m_buffer_num].yomi   , new_mrph->yomi);
            assert(strlen(ctx->m_buffer[ctx->m_buffer_num].midasi)
                   < MIDASI_MAX);
            assert(strlen(ctx->m_buffer[ctx->m_buffer_num].yomi) < YOMI_MAX);
	    ctx->m_buffer[ctx->m_buffer_num].length += strlen(new_mrph->midasi);
	    /* �����Ȥϸ��¦������Ѿ� */
	    ctx->m_buffer[ctx->m_buffer_num].weight = new_mrph->weight;
	    ctx->m_buffer[ctx->m_buffer_num].con_tbl = new_mrph->con_tbl;

            assert(i >= 0 && i < ctx->process_buffer_max);
            assert(ctx->p_buffer_num < ctx->process_buffer_max);
	    ctx->p_buffer[ctx->p_buffer_num] = ctx->p_buffer[i];
	    ctx->p_buffer[ctx->p_buffer_num].end = pos+strlen(new_mrph->midasi);
	    ctx->p_buffer[ctx->p_buffer_num].mrph_p = ctx->m_buffer_num;
	    ctx->p_buffer[ctx->p_buffer_num].score += (new_mrph->weight-pre_mrph->weight)
		*Class[new_mrph->hinsi][new_mrph->bunrui].cost
		*JOpt.cost_omomi.keitaiso;

	    if (++(ctx->m_buffer_num) == ctx->mrph_buffer_max) {
		realloc_mrph_buffer(ctx);
	        new_mrph = &ctx->m_buffer[m_num];	/* fixed by kuro 99/09/01 */
	    }
	    if (++(ctx->p_buffer_num) == ctx->process_buffer_max)
		realloc_process_buffer(ctx);
	}
    }
    return TRUE;
}

/*
------------------------------------------------------------------------------
  PROCEDURE: <through_word> ��̡������Ʃ�����
------------------------------------------------------------------------------
*/
    
int 	through_word(JCONTEXT* ctx, int pos , int m_num)
{
    int i, j, k, l, n, nn, sc, scmin;
    MRPH *now_mrph, *mrph_p;

    now_mrph = &ctx->m_buffer[m_num];
    if (!is_through(now_mrph)) return TRUE;

    for (l = 0; (i = (ctx->match_pbuf)[l]) >= 0; l++) {
      /* Assert - Added RX. 09/09 */
      if (!my_assert(ctx, l < ctx->process_buffer_max)
          || !my_assert(ctx, ctx->m_buffer_num <= ctx->mrph_buffer_max))
        ctx->error = 1;
      if (ctx->error)
        return FALSE;
	for (j = 0 ; j < (ctx->m_buffer_num) ; j++) {
	    mrph_p = &ctx->m_buffer[j];
	    if (mrph_p->hinsi   == now_mrph->hinsi   &&
		mrph_p->bunrui  == now_mrph->bunrui  &&
		mrph_p->con_tbl == ctx->m_buffer[ctx->p_buffer[i].mrph_p].con_tbl &&
		mrph_p->weight  == now_mrph->weight  &&
		strcmp(mrph_p->midasi, now_mrph->midasi) == 0 &&
		strcmp(mrph_p->yomi,   now_mrph->yomi  ) == 0) break;
	}
	if ((n = j) == (ctx->m_buffer_num)) {
	    /* ����ʸ����ǽ��ƽи����������פγ�̤Ǥ���С�ľ����
	       �����Ǥ�con_tbl��Ʃ�ᤵ����褦��con_tbl���Ѳ������ơ�
	       (ctx->m_buffer)���ɲä��� */
          /* Assert - Added RX. 09/09 */
          if (!my_assert(ctx, ctx->m_buffer_num < ctx->mrph_buffer_max)) {
            ctx->error = 1;
            return FALSE;
          }
	    ctx->m_buffer[ctx->m_buffer_num] = *now_mrph;

          /* Assert - Added RX. 09/09 */
          if (!my_assert(ctx, i >= 0 && i < ctx->process_buffer_max)
              || !my_assert(ctx,
                            ctx->p_buffer[i].mrph_p < ctx->mrph_buffer_max)) {
            ctx->error = 1;
            return FALSE;
          }
	    ctx->m_buffer[ctx->m_buffer_num].con_tbl
	      = ctx->m_buffer[ctx->p_buffer[i].mrph_p].con_tbl;
	    if (++(ctx->m_buffer_num) == (ctx->mrph_buffer_max)) {
		realloc_mrph_buffer(ctx);
		now_mrph = &ctx->m_buffer[m_num];	/* fixed by kuro 99/09/01 */
	    }
	}

	/* Ʃ�ᵬ§�˴�Ť�Ϣ�� */
	sc = (now_mrph->weight*JOpt.cost_omomi.keitaiso*
	      Class[now_mrph->hinsi][now_mrph->bunrui].cost);
	for (j = 0 ; j < (ctx->p_buffer_num) ; j++)
	  if (ctx->p_buffer[j].mrph_p == n && ctx->p_buffer[j].start == pos) break;
	if ((nn = j) == (ctx->p_buffer_num)) {
            /* Assert - Added RX. 09/09 */
          if (!my_assert(ctx, ctx->p_buffer_num < ctx->process_buffer_max)) {
            ctx->error = 1;
            return FALSE;
          }
	    /* ���Ƹ�����褦��Ʃ��ʤ顤(ctx->p_buffer)�˿������ɲä��� */
	    ctx->p_buffer[ctx->p_buffer_num].score = ctx->p_buffer[i].score+sc;
	    ctx->p_buffer[ctx->p_buffer_num].mrph_p = n;
	    ctx->p_buffer[ctx->p_buffer_num].start = pos;
	    ctx->p_buffer[ctx->p_buffer_num].end = pos + now_mrph->length;
	    ctx->p_buffer[ctx->p_buffer_num].path[0] = i;
	    ctx->p_buffer[ctx->p_buffer_num].path[1] = -1;
	    ctx->p_buffer[ctx->p_buffer_num].connect = TRUE;
	    if (++(ctx->p_buffer_num) == (ctx->process_buffer_max))
		realloc_process_buffer(ctx);
	} else {
	    /* (ctx->p_buffer)����ȯ���ɤ����ᡤ������(ctx->p_buffer)�λȤ��󤷤򤹤� */

            /* Assert - Added RX. 09/09 */
          if (!my_assert(ctx, nn >= 0 && nn < ctx->process_buffer_max)) {
            ctx->error = 1;
            return FALSE;
          }
	    for (j = 0 ; ctx->p_buffer[nn].path[j] != -1 ; j++) {}
            /* Assert - Added RX. 09/09 */
            if (!my_assert(ctx, j + 1 >= 0 && j + 1 < MAX_PATHES)) {
              ctx->error = 1;
              return FALSE;
            }
	    ctx->p_buffer[nn].path[j]   = i;
	    ctx->p_buffer[nn].path[j+1] = -1;

	    /* �����Ȥ��⤤��Τϻ޴��ꤹ�� */
	    scmin = INT_MAX;
	    for (j = 0 ; ctx->p_buffer[nn].path[j] != -1 ; j++)
	      if (scmin > ctx->p_buffer[ctx->p_buffer[nn].path[j]].score)
		scmin = ctx->p_buffer[ctx->p_buffer[nn].path[j]].score;
	    for (j = 0 ; ctx->p_buffer[nn].path[j] != -1 ; j++)
	      if (ctx->p_buffer[ctx->p_buffer[nn].path[j]].score
		  > scmin + JOpt.cost_omomi.cost_haba) {
                  for (k = j ; ctx->p_buffer[nn].path[k] != -1 ; k++) {
                    /* Assert - Added RX. 09/09 */
                    if (!my_assert(ctx, nn >= 0 && nn < ctx->process_buffer_max)
                        || !my_assert(ctx, k + 1 >= 0 && k + 1 < MAX_PATHES)) {
                      ctx->error = 1;
                      return FALSE;
                    }
		    ctx->p_buffer[nn].path[k] = ctx->p_buffer[nn].path[k+1];
                  }
		  j--;
	      }
	    ctx->p_buffer[nn].score = scmin+sc;
	}
    }
    return TRUE;
}

/*
------------------------------------------------------------------------------
  PROCEDURE: <is_through>
------------------------------------------------------------------------------
*/
    
int 	is_through(MRPH *mrph_p)
{
    if (
	/* ��̻Ϥ�Ʃ������򤷤ʤ� 2007/12/06
	(mrph_p->hinsi == JOpt.kakko_hinsi && mrph_p->bunrui == JOpt.kakko_bunrui1) ||
	*/
	(mrph_p->hinsi == JOpt.kakko_hinsi && mrph_p->bunrui == JOpt.kakko_bunrui2) ||
	(mrph_p->hinsi == JOpt.kuuhaku_hinsi && mrph_p->bunrui == JOpt.kuuhaku_bunrui))
	return TRUE;
    else 
	return FALSE;
}

/*
------------------------------------------------------------------------------
  PROCEDURE: <my_fprintf> (MS Windows �Τ��� �˽��Ϥ� SJIS �ˤ���)
                             >>> Added by Taku Kudoh <<<
------------------------------------------------------------------------------
*/
#ifdef _WIN32
void my_fprintf(FILE* output, const char *fmt, ...)
{
    va_list  ap;
    char     buf[1024];
#ifndef JUMAN_NO_EUC_CONVERSION
    char     *sjisstr;
#endif
    
    va_start(ap,fmt);
    vsprintf(buf,fmt,ap);
    va_end(ap);

    /* SJIS ���ѹ����ƽ��� */
#ifndef JUMAN_NO_EUC_CONVERSION
    sjisstr = toStringSJIS(buf);
    fwrite(sjisstr,sizeof(char),strlen(sjisstr),output);
#else
    fwrite(buf,sizeof(char),strlen(buf),output);
#endif
#ifndef JUMAN_NO_EUC_CONVERSION
    my_free(sjisstr);
#endif
}
#endif

MRPH *prepare_path_mrph(JCONTEXT* ctx, int path_num , int para_flag)
{
    MRPH       	*mrph_p;
    int        	j;

    mrph_p = &(ctx->m_buffer[ctx->p_buffer[path_num].mrph_p]);

    if (para_flag != 0 && is_through(mrph_p) == TRUE) return NULL;
    
    if (para_flag)
	strcpy(ctx->kigou, "@ ");
    else
	ctx->kigou[0] = '\0';
    assert(strlen(mrph_p->midasi) < MIDASI_MAX);
    strcpy(ctx->midasi1, mrph_p->midasi);
    strcpy(ctx->midasi2, *mrph_p->midasi2 ? mrph_p->midasi2 : mrph_p->midasi);
    assert(strlen(mrph_p->yomi) < MIDASI_MAX);
    strcpy(ctx->yomi, mrph_p->yomi);
    if ( (mrph_p->katuyou1 > 0) && (mrph_p->katuyou2 > 0) ) {
        assert(strlen(ctx->midasi1)
               + strlen(Form[mrph_p->katuyou1][mrph_p->katuyou2].gobi)
               < MIDASI_MAX);
	strcat(ctx->midasi1, Form[mrph_p->katuyou1][mrph_p->katuyou2].gobi);
	for(j = 1; strcmp(Form[mrph_p->katuyou1][j].name, BASIC_FORM); j++);
        assert(strlen(ctx->midasi2) + strlen(Form[mrph_p->katuyou1][j].gobi)
               < MIDASI_MAX);
	strcat(ctx->midasi2, Form[mrph_p->katuyou1][j].gobi);
        assert(strlen(ctx->yomi)
               + strlen(Form[mrph_p->katuyou1][mrph_p->katuyou2].gobi_yomi)
               < MIDASI_MAX);
	strcat(ctx->yomi, Form[mrph_p->katuyou1][mrph_p->katuyou2].gobi_yomi);
    }

    /* ��ʸ���ˤ����ɸ��ɽ���� */
    if (mrph_p->hinsi != 1 && mrph_p->hinsi != 15 &&
	strncmp(ctx->String + ctx->p_buffer[path_num].start, ctx->midasi1, mrph_p->length)) {
	strncpy(ctx->midasi1, ctx->String + ctx->p_buffer[path_num].start, mrph_p->length);
	if (strcmp(mrph_p->imis, NILSYMBOL)) {
	    mrph_p->imis[strlen(mrph_p->imis) - 1] = '\0';
	    strcat(mrph_p->imis, " ��ʸ����\"");
	}
	else {
	    strcpy(mrph_p->imis, "\"��ʸ����\"");
	}
    }

    return mrph_p;
}

/* unfragmented allocator */
static void* get_path_mrph_alloc(JCONTEXT* ctx, int size) {
  void* ptr;
  if (ctx->path_mrph_max == 0) {
    ctx->path_mrph_max = 128;
    /*ctx->path_mrph_max = 8192;*/  /* prealloc 8K. */
  }
  if (ctx->path_mrph_buff == NULL) {
    ctx->path_mrph_buff = (char*) my_alloc(ctx->path_mrph_max);
  }
  if (ctx->path_mrph_offs + size > ctx->path_mrph_max) {
    const int old_size = ctx->path_mrph_max;
    const char * const old_ptr = ctx->path_mrph_buff;
    for( ; ctx->path_mrph_offs + size > ctx->path_mrph_max
           ; ctx->path_mrph_max *= 2);
    ctx->path_mrph_buff = (char*) my_realloc(ctx->path_mrph_buff,
                                             ctx->path_mrph_max);
    if (ctx->path_mrph_buff != old_ptr) {
      int i;
      /* shift existing pointers */
      assert(ctx->OutputAVnum - 1 < ctx->OutputAVmax);
      for(i = 0 ; i < ctx->OutputAVnum ; i++) {
        if (ctx->OutputAV[i] != NULL) {
          const int buff_offset = (int) (ctx->OutputAV[i] - old_ptr);
          assert(buff_offset >= 0);
          assert(buff_offset >= 0 && buff_offset < old_size);
          ctx->OutputAV[i] = ctx->path_mrph_buff + buff_offset;
        }
      }
    }
  }
  ptr = (void*) ( ctx->path_mrph_buff + ctx->path_mrph_offs );
  ctx->path_mrph_last = size;
  ctx->path_mrph_offs += size;
  return ptr;
}

static void get_path_mrph_free_last(JCONTEXT* ctx, void* ptr) {
  if ( ( (char*) ptr ) + ctx->path_mrph_last
       == ctx->path_mrph_buff + ctx->path_mrph_offs) {
    ctx->path_mrph_offs -= ctx->path_mrph_last;
    ctx->path_mrph_last = 0;
  }
}

/* convenient formatting  written by X. Roche */
static char* format_mrph(JCONTEXT* ctx, MRPH *mrph_p) {
  const char* fmt = JOpt.Show_Opt_fmt;
  int len;
  char* ret;
  int work;
  for(work = 0 ; work < 2 ; work++) {  /* second pass write strings */
    int i;
    if (work)
      ret = (char *) get_path_mrph_alloc(ctx, len);
    len = 0;
    for(i = 0 ; fmt[i] ; i++) {
      if (fmt[i] == '%') {
        const char* tocopy = "?format?";    /* format error */
        char numeric[22];    /* (long enough for 64-bit) */
        switch (fmt[++i]) {
        case '%':  /* unescaping */
          strcpy(numeric, "%");
          tocopy = numeric;
          break;
        case 'g':  /* kigou */
          tocopy = ctx->kigou;
          break;
        case 'm':  /* midasi[0|1|2] */
          if (fmt[++i] == '0')
            tocopy = mrph_p->midasi;
          else if (fmt[i] == '1')
            tocopy = ctx->midasi1;
          else if (fmt[i] == '2')
            tocopy = ctx->midasi2;
          break;
        case 'y':  /* yomi */
          tocopy = ctx->yomi;
          break;
        case 'h':  /* hinsi[numeric|string] */
          if (fmt[++i] == 'n') {
            sprintf(numeric, "%d", mrph_p->hinsi);
            tocopy = numeric;
          } else if (fmt[i] == 's') {
            tocopy = Class[mrph_p->hinsi][0].id, mrph_p->hinsi;
          }
          break;
        case 'b':  /* bunrui[numeric|string] */
          if (fmt[++i] == 'n') { 
            sprintf(numeric, "%d", mrph_p->bunrui);
            tocopy = numeric;
          } else if (fmt[i] == 's') {
            tocopy = mrph_p->bunrui
              ?  (const char*)Class[mrph_p->hinsi][mrph_p->bunrui].id : "*";
          }
          break;
        case 'k':  /* katuyou[1|2][numeric|string] */
          if (fmt[++i] == '1') {
            if (fmt[++i] == 'n') {
              sprintf(numeric, "%d", mrph_p->katuyou1);
              tocopy = numeric;
            } else if (fmt[i] == 's') {
              tocopy = mrph_p->katuyou1
                ?  (const char*)Type[mrph_p->katuyou1].name
                : "*";
            }
          } else if (fmt[i] == '2') {
            if (fmt[++i] == 'n') {
              sprintf(numeric, "%d", mrph_p->katuyou2);
              tocopy = numeric;
            } else if (fmt[i] == 's') {
              tocopy = mrph_p->katuyou2
                ? (const char*)Form[mrph_p->katuyou1][mrph_p->katuyou2].name
                : "*";
            }
          }
          break;
        case 'i':  /* imis */
          tocopy = mrph_p->imis;
          break;
        case 'w':
          sprintf(numeric, "%d", mrph_p->weight);
          tocopy = numeric;
          break;
        }
        if (tocopy != NULL) {
          if (work)
            strcpy(&ret[len], tocopy);
          len += (int) strlen(tocopy);
        }
      } else if (fmt[i] == '\\' && fmt[i + 1] >= '0' && fmt[i + 1] <= '9') {
        int charnum = 0;
        for(i++ ; fmt[i] >= '0' && fmt[i] <= '9' ; i++) {
          charnum *= 10;
          charnum += ( fmt[i] - '0' );
        }
        i--;
        if (charnum < 255) {
          if (work)
            ret[len] = charnum;
          len++;
        } else {
          const char *errfmt = "?format?";
          if (work)
            strcpy(&ret[len], errfmt);
          len += (int) strlen(errfmt);
        }
      } else if (fmt[i] == '\\') {
        char c = '?';
        switch(fmt[++i] ) {
        case '\\':
          c = '\\';
          break;
        case 'a':
          c = '\a';
          break;
        case 'b':
          c = '\b';
          break;
        case 'f':
          c = '\f';
          break;
        case 'n':
          c = '\n';
          break;
        case 'r':
          c = '\r';
          break;
        case 't':
          c = '\t';
          break;
        case 'v':
          c = '\v';
          break;
        }
        if (work)
          ret[len] = c;
        len++;
      } else {
        if (work)
          ret[len] = fmt[i];
        len++;
      }
    }
    if (work)
      ret[len] = 0;
    len++;
  }
  return ret;
}

char *get_path_mrph(JCONTEXT* ctx, int path_num , int para_flag)
{
    int len = 0;
    MRPH *mrph_p;
    char *ret;

    if ((mrph_p = prepare_path_mrph(ctx, path_num, para_flag)) == NULL) return NULL;
    len = strlen(ctx->kigou)+strlen(ctx->midasi1)+strlen(ctx->yomi)+strlen(ctx->midasi2)+strlen(Class[mrph_p->hinsi][0].id)+mrph_p->hinsi/10+1;

    if ( mrph_p->bunrui ) {
	len += strlen(Class[mrph_p->hinsi][mrph_p->bunrui].id);
    }
    else {
	len += 1;
    }

    len += mrph_p->bunrui/10+1;
	
    if ( mrph_p->katuyou1 ) { 
	len += strlen(Type[mrph_p->katuyou1].name);
    }
    else {
	len += 1;
    }

    len += mrph_p->katuyou1/10+1;
	
    if ( mrph_p->katuyou2 ) {
	len += strlen(Form[mrph_p->katuyou1][mrph_p->katuyou2].name);
    }
    else {
	len += 1;
    }

    len += mrph_p->katuyou2/10+1;

    len += 12;	/* ��� 10, ���� 1, ��ü 1 */

    switch (JOpt.Show_Opt2) {
    case Op_E2:
	len += strlen(mrph_p->imis) + 1;
	ret = (char *) get_path_mrph_alloc(ctx, len);
	sprintf(ret, "%s%s %s %s %s %d %s %d %s %d %s %d %s\n", (ctx->kigou), (ctx->midasi1), (ctx->yomi), (ctx->midasi2), 
		Class[mrph_p->hinsi][0].id, mrph_p->hinsi, 
		mrph_p->bunrui ? Class[mrph_p->hinsi][mrph_p->bunrui].id : (U_CHAR *)"*", mrph_p->bunrui, 
		mrph_p->katuyou1 ? Type[mrph_p->katuyou1].name : (U_CHAR *)"*", mrph_p->katuyou1, 
		mrph_p->katuyou2 ? Form[mrph_p->katuyou1][mrph_p->katuyou2].name : (U_CHAR *)"*", mrph_p->katuyou2, 
		mrph_p->imis);
	break;
    case Op_E:
	ret = (char *) get_path_mrph_alloc(ctx, len);
	sprintf(ret, "%s%s %s %s %s %d %s %d %s %d %s %d\n", (ctx->kigou), (ctx->midasi1), (ctx->yomi), (ctx->midasi2), 
		Class[mrph_p->hinsi][0].id, mrph_p->hinsi, 
		mrph_p->bunrui ? Class[mrph_p->hinsi][mrph_p->bunrui].id : (U_CHAR *)"*", mrph_p->bunrui, 
		mrph_p->katuyou1 ? Type[mrph_p->katuyou1].name : (U_CHAR *)"*", mrph_p->katuyou1, 
		mrph_p->katuyou2 ? Form[mrph_p->katuyou1][mrph_p->katuyou2].name : (U_CHAR *)"*", mrph_p->katuyou2);
	break;
    case Op_EF:
      ret = format_mrph(ctx, mrph_p);
      break;
    }
    return ret;
}

int get_best_path_num(JCONTEXT* ctx)
{
    int j, last;

    j = 0;
    last = ctx->p_buffer_num -1;
    do {
        assert(last >= 0 && last < ctx->process_buffer_max);
	last = ctx->p_buffer[last].path[0];
        assert(j >= 0 && j < ctx->process_buffer_max);
	ctx->path_buffer[j] = last;
	j++;
    } while ( ctx->p_buffer[last].path[0] );

    return j;
}

/*
------------------------------------------------------------------------------
  PROCEDURE: <print_path_mrph> �����Ǥ�ɽ��      >>> changed by yamaji <<<
------------------------------------------------------------------------------
*/
/*
  �����С��⡼���б��Τ��ᡢ����output�����䤷�ƽ�������ѹ����ǽ�ˤ��롣
  NACSIS �Ȳ�
*/
/* para_flag != 0 �ʤ� @���� */
void print_path_mrph(JCONTEXT* ctx, FILE* output, int path_num , int para_flag)
{
    PROCESS_BUFFER	*proc_p;
    MRPH       	*mrph_p;
    int		newDicNo;
    int         now_r_buffer_num;
    MRPH        r_last_mrph;
    int		pos;
    int        	i, j, k, len;

    if ((mrph_p = prepare_path_mrph(ctx, path_num, para_flag)) == NULL) return;
    proc_p = &(ctx->p_buffer[path_num]);
    pos = proc_p->start;

    fputs((ctx->kigou), output);

    switch (JOpt.Show_Opt2) {
    case Op_F: 
	len = strlen((ctx->yomi)); (ctx->yomi)[len] = ')'; (ctx->yomi)[len+1] = '\0';
	my_fprintf(output, "%-12.12s(%-12.12s%-10.10s %-14.14s",
		(ctx->midasi1), (ctx->yomi), (ctx->midasi2),
		Class[mrph_p->hinsi][mrph_p->bunrui].id);
	if (mrph_p->katuyou1)
	    my_fprintf(output, " %-14.14s %-12.12s",
		    Type[mrph_p->katuyou1].name,
		    Form[mrph_p->katuyou1][mrph_p->katuyou2].name);
	fputc('\n', output);
	break;
	
    case Op_C:
	my_fprintf(output, "%s %s %s %d %d %d %d\n",
                   ctx->midasi1, ctx->yomi, ctx->midasi2,
		mrph_p->hinsi, mrph_p->bunrui,
		mrph_p->katuyou1, mrph_p->katuyou2);
	break;

    case Op_EE:
	/* ��ƥ����ΤĤʤ����ɽ�� */
	fprintf(output, "%d ", path_num);
	for (i = 0; proc_p->path[i] != -1; i++) {
	    if (i) fprintf(output, ";");
	    fprintf(output, "%d", proc_p->path[i]);
	}
	fprintf(output, " ");

	fprintf(output, "%d ", pos);
	if (!strcmp(ctx->midasi1, "\\ ")) pos++; else pos += strlen(ctx->midasi1);
	fprintf(output, "%d ", pos);
	/* -E ���ץ����Ϥ�����ʬ�����ɲ�,
	   ���θ�� -e -e2 ���ץ�����Ʊ�ͤν��Ϥ򤹤�Τ� break ���ʤ� */

    case Op_E:
    case Op_E2:
	my_fprintf(output, "%s %s %s ", ctx->midasi1, ctx->yomi, ctx->midasi2);
	
	my_fprintf(output, "%s ", Class[mrph_p->hinsi][0].id);
	fprintf(output, "%d ", mrph_p->hinsi);
	
	if ( mrph_p->bunrui ) 
	  my_fprintf(output, "%s ", Class[mrph_p->hinsi][mrph_p->bunrui].id);
	else
	  my_fprintf(output, "* ");
	fprintf(output, "%d ", mrph_p->bunrui);
	
	if ( mrph_p->katuyou1 ) 
	  my_fprintf(output, "%s ", Type[mrph_p->katuyou1].name);
	else                    
	  fprintf(output, "* ");
	fprintf(output, "%d ", mrph_p->katuyou1);
	
	if ( mrph_p->katuyou2 ) 
	  my_fprintf(output, "%s ", Form[mrph_p->katuyou1][mrph_p->katuyou2].name);
	else 
	  fprintf(output, "* ");
	fprintf(output, "%d", mrph_p->katuyou2);

	if (JOpt.Show_Opt2 == Op_E) {
	    fprintf(output, "\n");	/* -e �Ǥ� imis �Ͻ��Ϥ��ʤ� */
	    break;
	}

	/* for SRI
	   fprintf(stdout, "\n");
	   if (para_flag) fprintf(stdout , "@ ");
	   */

	my_fprintf(output, " %s\n", mrph_p->imis);
	break;
    case Op_EF:
      {
        char *ret = format_mrph(ctx, mrph_p);
        fprintf(output, "%s", ret);
        get_path_mrph_free_last(ctx, ret);
      }

    }
}

void process_path_mrph(JCONTEXT* ctx, FILE* output,
                       int path_num , int para_flag) {
    if (output) {
      print_path_mrph(ctx, output, path_num, para_flag);
    }
    else if (ctx->OutputAVfun != NULL) {
      char *p = get_path_mrph(ctx, path_num, para_flag);
      ctx->OutputAVfun(ctx, p);
      get_path_mrph_free_last(ctx, p);
    }
    else {
      char *p;
      if (ctx->OutputAVmax == 0) {
        ctx->OutputAVmax = 10;
        ctx->OutputAV = (char **)my_alloc(sizeof(char *)*(ctx->OutputAVmax));
      }
      else if (ctx->OutputAVnum >= ctx->OutputAVmax-1) {
        ctx->OutputAV
          = (char **)my_realloc(ctx->OutputAV,
                                sizeof(char *)*((ctx->OutputAVmax) <<= 1));
      }
      p =  get_path_mrph(ctx, path_num, para_flag);
      if (p != NULL) {
        assert(ctx->OutputAVnum >= 0
               && ctx->OutputAVnum + 1 < ctx->OutputAVmax);
        ctx->OutputAV[ctx->OutputAVnum++] = p;
        ctx->OutputAV[ctx->OutputAVnum] =  NULL;
      }
    }
}

/*
------------------------------------------------------------------------------
  PROCEDURE: <print_best_path> ������Ĺ���פ�PATH��Ĵ�٤�
------------------------------------------------------------------------------
*/
/*
  �����С��⡼���б��Τ��ᡢ����output�����䤷�ƽ�������ѹ����ǽ�ˤ��롣
  NACSIS �Ȳ�
*/
char **print_best_path(JCONTEXT* ctx, FILE* output)
{
    int i, j, last;
    MRPH *mrph_p,*mrph_p1;

    j = 0;
    last = (ctx->p_buffer_num)-1;
    do {
        assert(last >= 0 && last < ctx->process_buffer_max);
	last = ctx->p_buffer[last].path[0];
        assert(j >= 0 && j < ctx->process_buffer_max);
	ctx->path_buffer[j] = last;
	j++;
    } while ( ctx->p_buffer[last].path[0] );

    /* ��̤� buffer ��������� */
    if (!output) {
	ctx->OutputAVnum = 0;
    }

    for ( i=j-1; i>=0; i-- ) {
        assert(i >= 0 && i < ctx->process_buffer_max);
	process_path_mrph(ctx, output, ctx->path_buffer[i] , 0);
    }
    return (ctx->OutputAV);	/* ��Ǥ����� free ���뤳�� */
}

/*
------------------------------------------------------------------------------
  PROCEDURE: <print_all_mrph> ���������Ϸ�̤˴ޤޤ�����Ƥη�����
------------------------------------------------------------------------------
*/
/*
  �����С��⡼���б��Τ��ᡢ����output�����䤷�ƽ�������ѹ����ǽ�ˤ��롣
  NACSIS �Ȳ�
*/
char **print_all_mrph(JCONTEXT* ctx, FILE* output)
{
    int  i, j, k;
    MRPH mrph;

    assert(ctx->m_buffer_num - 1 < ctx->mrph_buffer_max);
    for (i = 0 ; i < ctx->m_buffer_num ; i++)
	ctx->m_check_buffer[i] = 0;
    
    _print_all_mrph(ctx, output, (ctx->p_buffer_num)-1);
    ctx->m_check_buffer[0] = 0;

    /* ��̤� buffer ��������� */
    if (!output) {
	ctx->OutputAVnum = 0;
    }

    for (i = 0 ; i < (ctx->m_buffer_num) ; i++)
	if ((ctx->m_check_buffer)[i])
	    process_path_mrph(ctx, output, i , 0);

    return (ctx->OutputAV);	/* ��Ǥ����� free ���뤳�� */
}

void _print_all_mrph(JCONTEXT* ctx, FILE* output, int path_num)
{
    int i;
    
    assert(path_num >= 0 && path_num < ctx->process_buffer_max);
    for (i = 0 ; ctx->p_buffer[path_num].path[i] != -1 ; i++) {
        assert(i >= 0 && i < MAX_PATHES);
        assert(ctx->p_buffer[path_num].path[i] < ctx->mrph_buffer_max);
	if (!ctx->m_check_buffer[ctx->p_buffer[path_num].path[i]]) {
	    ctx->m_check_buffer[ctx->p_buffer[path_num].path[i]] = 1;
	    _print_all_mrph(ctx, output, ctx->p_buffer[path_num].path[i]);
	}
    }
}
/*
------------------------------------------------------------------------------
  PROCEDURE: <print_all_path> ���������Ϸ�̤˴ޤޤ�����Ƥ�PATH
------------------------------------------------------------------------------
*/
/*
  �����С��⡼���б��Τ��ᡢ����output�����䤷�ƽ�������ѹ����ǽ�ˤ��롣
  NACSIS �Ȳ�
*/
char **print_all_path(JCONTEXT* ctx, FILE* output)
{
/*  int i,j;
    for (i = 0 ; i < (ctx->p_buffer_num) ; i++) {
	printf("%d %s %d %d --- " , i , ctx->m_buffer[ctx->p_buffer[i].mrph_p].midasi ,
	       ctx->p_buffer[i].start , ctx->p_buffer[i].end);
	for (j = 0 ; ctx->p_buffer[i].path[j] != -1 ; j++)
	  printf("%d ",ctx->p_buffer[i].path[j]);
	printf("\n");
    }*/

    /* ��̤� buffer ��������� */
    if (!output) {
	ctx->OutputAVnum = 0;
    }

    _print_all_path(ctx, output, (ctx->p_buffer_num)-1, 0);
    return (ctx->OutputAV);	/* ��Ǥ����� free ���뤳�� */   
}

void _print_all_path(JCONTEXT* ctx, FILE* output, int path_num, int pathes)
{
    int i, j;
    
    assert(path_num >= 0 && path_num < ctx->process_buffer_max);
    for ( i=0; ctx->p_buffer[path_num].path[i] != -1; i++ ) {
	if ( ctx->p_buffer[path_num].path[0] == 0 ) {
            assert(pathes-1 >= 0 && pathes-1 < ctx->process_buffer_max);
            for ( j=pathes-1; j>=0; j-- ) {
	      process_path_mrph(ctx, output, ctx->path_buffer[j] , 0);
            }
	    if (output) fprintf(output, "EOP\n");
	} else {
            assert(pathes >= 0 && pathes < ctx->process_buffer_max);
            assert(i >= 0 && i < MAX_PATHES);
	    ctx->path_buffer[pathes] = ctx->p_buffer[path_num].path[i];
	    _print_all_path(ctx, output, ctx->p_buffer[path_num].path[i], pathes+1);
	}
    }
}

/*
------------------------------------------------------------------------------
  PROCEDURE: <print_homograph_path> ʣ���θ����Ȥ������Ǥ���󤹤�
------------------------------------------------------------------------------
*/
/*
  �����С��⡼���б��Τ��ᡢ����output�����䤷�ƽ�������ѹ����ǽ�ˤ��롣
  NACSIS �Ȳ�
*/
char **print_homograph_path(JCONTEXT* ctx, FILE* output)
{
    ctx->path_buffer[0] = ctx->p_buffer_num - 1;
    ctx->path_buffer[1] = -1;

    /* ��̤� buffer ��������� */
    if (!output) {
	ctx->OutputAVnum = 0;
    }

    _print_homograph_path(ctx, output, 0, 0, 2);
    if (!ctx->error)
      return (ctx->OutputAV);	/* ��Ǥ����� free ���뤳�� */

    return NULL;
}

/* Stack limit on */
#if (defined(_WIN32) && defined(_M_IX86)) \
    || (defined(__linux) && defined(__i386)) \
    || (defined(__sun) && defined(_ILP32))
#define MAX_STACK 512
#else
#define MAX_STACK 1024
#endif

int _print_homograph_path(JCONTEXT* ctx, FILE* output,
                          const int level, int pbuf_start, int new_p)
{
    int i, j, k, l, now_pos, len, ll, pt, pt2, f;

    /* stack check */
    if (level > ctx->max_level)
      ctx->max_level = level;
    if (!my_assert(ctx, level < MAX_STACK)) {
      ctx->error = 1; /* Overflow - Added RX. 06/06 */
      return 0;
    }

    assert(pbuf_start >= 0 && pbuf_start < ctx->process_buffer_max);
    assert(ctx->path_buffer[pbuf_start] >= 0
           && ctx->path_buffer[pbuf_start] < ctx->process_buffer_max);
    if (ctx->p_buffer[ctx->path_buffer[pbuf_start]].path[0] == 0) {
	/* ��Ƭ�ޤǥ�󥯤򤿤ɤ꽪��ä� */
	for (j = new_p-2; j >= 1; j--) {
	    /* Ʊ���۵��췲��쵤�˽��� */
	    for ( ; ctx->path_buffer[j] >= 0; j--) {}
	    for (k = j+1, l = 0; ctx->path_buffer[k] >= 0; k++) {
                assert(k >= 0 && k < ctx->process_buffer_max);
		process_path_mrph(ctx, output, ctx->path_buffer[k] , l++);
	    }
	}
	if (JOpt.Show_Opt1 == Op_BB) return(1);
	if (output) fprintf(output, "EOP\n");
	return(0);
    }

    /* �ü�ͥ�赬§
           3ʸ����ʣ���� 2-1
	   4ʸ����ʣ���� 2-2
	   5ʸ����ʣ���� 3-2
       ��ʬ�䤵��뤳�Ȥ�¿���Τǡ�����ʬ���ͥ��Ū�˽��Ϥ���褦�ˤ��롥
       ���Τ��ᡤ
       ��2ʸ����κ���2,3,4ʸ���줬Ϣ�ܤ��Ƥ������2ʸ�����ͥ��
       ������ʳ��ʤ��ʸ�����ξ��ʤ����ͥ��
       �Ȥ��롥 */
    f = 0;
    now_pos = ctx->p_buffer[ctx->path_buffer[pbuf_start]].start;
    for (j = pbuf_start; ctx->path_buffer[j] >= 0; j++)
	for (i = 0; (pt = ctx->p_buffer[ctx->path_buffer[j]].path[i]) != -1; i++)
	    /* 2ʸ�����õ�� */
	    if (ctx->p_buffer[pt].start == now_pos-2*2) {
		for (k = 0; (pt2 = ctx->p_buffer[pt].path[k]) != -1; k++)
		    /* 2ʸ����κ���Ϣ�ܤ��Ƥ���줬2��4ʸ���줫�� */
		    if (ctx->p_buffer[pt2].start <= now_pos-(2+2)*2 &&
			ctx->p_buffer[pt2].start >= now_pos-(2+4)*2) f = 1;
	    }

    for (ll = 1; ll <= now_pos; ll++) { /* Ⱦ��ʸ���Τ��ᡤ1byte���Ȥ˽��� */
	len = ll;
	if (f)
	    /* 1ʸ�����2ʸ�����ͥ���̤������ؤ��� */
	    if (ll == 2) len = 4; else if (ll == 4) len = 2;

	/* Ʊ��Ĺ���η����Ǥ����ƥꥹ�ȥ��åפ��� */
	l = new_p;
	for (j = pbuf_start; ctx->path_buffer[j] >= 0; j++) {
	    for (i = 0; (pt = ctx->p_buffer[ctx->path_buffer[j]].path[i]) != -1; i++) {
		if (ctx->p_buffer[pt].start == now_pos-len) {
		    /* Ʊ���۵��췲�����(â����ʣ���ʤ��褦�ˤ���) */
		    for (k = new_p; k < l; k++)
			if (ctx->path_buffer[k] == pt) break;
		    if (k == l) {
                      if (!my_assert(ctx, l >= 0 && l < ctx->process_buffer_max))
                        return 0;  /* Overflow - Added RX. 06/06 */
                      assert(l >= 0 && l < ctx->process_buffer_max);
                      ctx->path_buffer[l++] = pt;
                    }
		}
	    }
	}
        if (!my_assert(ctx, l >= 0 && l < ctx->process_buffer_max))
          return 0;  /* Overflow - Added RX. 06/06 */
        assert(l >= 0 && l < ctx->process_buffer_max);
	ctx->path_buffer[l] = -1; /* Ʊ���۵��췲�Υ���ɥޡ��� */
	if (l != new_p)
	    if (_print_homograph_path(ctx, output, level+1, new_p, l+1)) return(1);
        if (ctx->error)
          return 0;
    }
    return(0);
}

/*
------------------------------------------------------------------------------
  PROCEDURE: <pos_match_process> <pos_right_process>
------------------------------------------------------------------------------
*/
int pos_match_process(JCONTEXT* ctx, int pos, int p_start)
{
    int i, j;

    /* ���֤��ޥå����� (ctx->p_buffer) ����Ф��ơ�(ctx->match_pbuf) �˽��¤٤� */
    j = 0;
    assert(p_start >= 0 && ctx->p_buffer_num <= ctx->process_buffer_max);
    for (i = p_start; i < ctx->p_buffer_num; i++) {
	if (ctx->p_buffer[i].end <= pos || ctx->p_buffer[i].connect == FALSE) {
	    if (i == p_start)
	      /* p_start ������ (ctx->p_buffer) �Ͻ�ʬ pos ���������Τǡ�õ�����ά */
	      p_start++;
	    if (ctx->p_buffer[i].end == pos
                && ctx->p_buffer[i].connect == TRUE) {
              assert(j >= 0 && j < ctx->process_buffer_max);
	      ctx->match_pbuf[j++] = i;
            }
	}
    }
    assert(j >= 0 && j < ctx->process_buffer_max);
    ctx->match_pbuf[j] = -1;

    return p_start;
}

int pos_right_process(JCONTEXT* ctx, int pos)
{
    int	i;

    assert(ctx->p_buffer_num <= ctx->process_buffer_max);
    for ( i=0; i<ctx->p_buffer_num; i++ )
      if ( ctx->p_buffer[i].end > pos )
	return 1;
    
    return 0;
}

/*
------------------------------------------------------------------------------
  PROCEDURE: <check_connect>			Changed by yamaji
------------------------------------------------------------------------------
*/

int check_connect(JCONTEXT* ctx, int pos, int m_num, int dakuon_flag)
{
    int chk_con_num;
    int i, j, pathes;
    int	score, best_score, haba_score, best_score_num;
    int c_score, class_score;
    MRPH *new_mrph;
    MRPH *pre_mrph;
    int left_con, right_con;
    CONNECT_COST *c_cache;

    assert(m_num >= 0 && m_num < ctx->mrph_buffer_max);

    new_mrph = &ctx->m_buffer[m_num];

    assert(new_mrph->hinsi >= 0);
    assert(new_mrph->bunrui >= 0);
    
    best_score = INT_MAX;  /* maximam value of int */
    chk_con_num = 0;
    score = class_score = best_score_num = 0;
    class_score = Class[new_mrph->hinsi][new_mrph->bunrui].cost 
	* new_mrph->weight * JOpt.cost_omomi.keitaiso;

    /* Ϣ�ܥ���å���˥ҥåȤ���С�õ����Ԥ�ʤ� */
    c_cache = &ctx->connect_cache[rensetu_tbl[new_mrph->con_tbl].j_pos];
    if (JOpt.Show_Opt_debug == 0) {
	if (c_cache->pos == pos && c_cache->dakuon_flag == dakuon_flag 
	    && c_cache->p_no > 0) {
            assert(ctx->p_buffer_num >= 0
                   && ctx->p_buffer_num < ctx->process_buffer_max);
	    ctx->p_buffer[ctx->p_buffer_num].score = c_cache->cost + class_score;
	    ctx->p_buffer[ctx->p_buffer_num].mrph_p = m_num;
	    ctx->p_buffer[ctx->p_buffer_num].start = pos;
	    ctx->p_buffer[ctx->p_buffer_num].end = pos + new_mrph->length;
            assert(c_cache->p_no >= 0
                   && c_cache->p_no < ctx->process_buffer_max);
	    for (i = 0; (ctx->p_buffer[ctx->p_buffer_num].path[i] = ctx->p_buffer[c_cache->p_no].path[i]) >= 0; i++) {
              assert(c_cache->p_no < ctx->process_buffer_max);
              assert(i >= 0 && i < MAX_PATHES);
            }
            assert(i >= 0 && i < MAX_PATHES);
            assert(ctx->p_buffer_num >= 0
                   && ctx->p_buffer_num < ctx->process_buffer_max);
	    ctx->p_buffer[ctx->p_buffer_num].path[i] = -1;
	    ctx->p_buffer[ctx->p_buffer_num].connect = TRUE;
	    if (++(ctx->p_buffer_num) == ctx->process_buffer_max)
		realloc_process_buffer(ctx);
	    return TRUE;
	}
    }

    for (i = 0; (j = ctx->match_pbuf[i]) >= 0; i++) {

	/* �����η����Ǥ�con_tbl����Ф� */
	left_con = ctx->m_buffer[ctx->p_buffer[j].mrph_p].con_tbl;
	/* �����������Ǥ�con_tbl����Ф� */
	right_con = new_mrph->con_tbl;

	c_score = check_matrix(left_con , right_con);

	/* ����������Τ�ľ���η����Ǥ�̾�졢�ޤ���ư���Ϣ�ѷ���̾�����������ξ��Τ� */
	/* ľ���η����Ǥ��������ξ������ʿ��̾1ʸ���Ȥʤ��Τ��Բ� */
	/* weight=255�ΤȤ����Բ� */
	if (dakuon_flag &&
	    (!(ctx->m_buffer[ctx->p_buffer[j].mrph_p].hinsi == 6 ||
	       ctx->m_buffer[ctx->p_buffer[j].mrph_p].hinsi == 2 &&
	       ctx->m_buffer[ctx->p_buffer[j].mrph_p].katuyou2 == 8 ||
	       ctx->m_buffer[ctx->p_buffer[j].mrph_p].hinsi == 14 &&
	       ctx->m_buffer[ctx->p_buffer[j].mrph_p].bunrui < 5) ||
	     (ctx->m_buffer[ctx->p_buffer[j].mrph_p].hinsi != 14 &&
	      check_code(ctx->m_buffer[ctx->p_buffer[j].mrph_p].midasi, 0) == HIRAGANA &&
	      ctx->m_buffer[ctx->p_buffer[j].mrph_p].length == 2) ||
	     new_mrph->weight == 255))
	    c_score = 0;

	if (c_score) {
	    ctx->chk_connect[chk_con_num].pre_p = j;

	    /* calculate the score */
            assert(j >= 0 && j < ctx->process_buffer_max);
	    score = ctx->p_buffer[j].score + c_score * JOpt.cost_omomi.rensetsu;

	    ctx->chk_connect[chk_con_num].score = score;
	    if (score < best_score) {
		best_score = score;
		best_score_num = chk_con_num;
	    }
	    if (++chk_con_num >= MAX_PATHES_WK)
              return FALSE;
	}

	/* �ǥХ��ѥ�����ɽ�� */

	if (JOpt.Show_Opt_debug == 2 || (JOpt.Show_Opt_debug == 1 && c_score)) {

	    juman_log_err("%3d " , pos);

	    pre_mrph = &ctx->m_buffer[ctx->p_buffer[j].mrph_p];
	    juman_log_err("%s" , pre_mrph->midasi);
	    if (Class[pre_mrph->hinsi][pre_mrph->bunrui].kt)
		juman_log_err("%s", Form[pre_mrph->katuyou1][pre_mrph->katuyou2].gobi);
	    if (Class[pre_mrph->hinsi][0].id) {
		juman_log_err("(%s" , Class[pre_mrph->hinsi][0].id);
		if (pre_mrph->bunrui)
		    juman_log_err("-%s", Class[pre_mrph->hinsi][pre_mrph->bunrui].id);
		if (pre_mrph->katuyou1)
		    juman_log_err("-%s", Type[pre_mrph->katuyou1].name);
		if (pre_mrph->katuyou2)
		    juman_log_err("-%s", Form[pre_mrph->katuyou1][pre_mrph->katuyou2].name);
		juman_log_err(")");
	    }
	    juman_log_err("[= %d]", ctx->p_buffer[j].score);

	    if (c_score) {
		juman_log_err("--[+%d*%d]--", c_score, JOpt.cost_omomi.rensetsu);
	    } else {
		juman_log_err("--XXX--");
	    }

	    juman_log_err("%s" , new_mrph->midasi);
	    if (Class[new_mrph->hinsi][new_mrph->bunrui].kt)
		juman_log_err("%s", Form[new_mrph->katuyou1][new_mrph->katuyou2].gobi);
	    if (Class[new_mrph->hinsi][0].id) {
		juman_log_err("(%s" , Class[new_mrph->hinsi][0].id);
		if (new_mrph->bunrui)
		    juman_log_err("-%s",Class[new_mrph->hinsi][new_mrph->bunrui].id);
		if (new_mrph->katuyou1)
		    juman_log_err("-%s", Type[new_mrph->katuyou1].name);
		if (new_mrph->katuyou2)
		    juman_log_err("-%s", Form[new_mrph->katuyou1][new_mrph->katuyou2].name);
		juman_log_err(")");
	    }

	    if (c_score == 0) {
		juman_log_err("\n");
	    } else {
		juman_log_err("[+%d*%d.%d*%d = %d]\n", 
			Class[new_mrph->hinsi][new_mrph->bunrui].cost,
			new_mrph->weight/10, new_mrph->weight%10, 
			JOpt.cost_omomi.keitaiso*10, 
			/* = class_score */
			ctx->p_buffer[j].score + c_score * JOpt.cost_omomi.rensetsu + class_score);
	    }
	}
    }

    /* return immidiately, because if best_score is
       INT_MAX then no path exists. */
    if (best_score == INT_MAX) return TRUE;

    /* �����Ϣ�ܤ��ͻҤ�Ϣ�ܥ���å��������� */
    c_cache->p_no = ctx->p_buffer_num;
    c_cache->cost = best_score;
    c_cache->pos = pos;
    c_cache->dakuon_flag = dakuon_flag;

    /* ��괺�����٥��ȥѥ���1�Ĥ�0�֤���Ͽ */
    assert(best_score_num >= 0 && best_score_num < MAX_PATHES_WK);
    assert(ctx->p_buffer_num >= 0
           && ctx->p_buffer_num < ctx->process_buffer_max);
    ctx->p_buffer[ctx->p_buffer_num].path[0] = ctx->chk_connect[best_score_num].pre_p;
    pathes = 1;
    haba_score = best_score + JOpt.cost_omomi.cost_haba;
    assert(chk_con_num - 1 >= 0 && chk_con_num - 1 < MAX_PATHES_WK);
    for (j = 0; j < chk_con_num; j++) { /* ����ʳ��Υѥ����ɲ� */
      if (ctx->chk_connect[j].score <= haba_score && j != best_score_num) {
        /* Overflow - Added RX. 06/06 */
        if (!my_assert(ctx, pathes >= 0 && pathes < MAX_PATHES))
          break ;
        assert(pathes >= 0 && pathes < MAX_PATHES);
	ctx->p_buffer[ctx->p_buffer_num].path[pathes++]
          = ctx->chk_connect[j].pre_p;
      }
    }
    /* Overflow - Added RX. 06/06 */
    if (!my_assert(ctx, pathes >= 0 && pathes < MAX_PATHES))
      ctx->error = 1;
    if (ctx->error)
      return FALSE;
    assert(pathes >= 0 && pathes < MAX_PATHES);
    assert(ctx->p_buffer_num >= 0
           && ctx->p_buffer_num < ctx->process_buffer_max);
    ctx->p_buffer[ctx->p_buffer_num].path[pathes] = -1;

    ctx->p_buffer[ctx->p_buffer_num].score = best_score+class_score;
    ctx->p_buffer[ctx->p_buffer_num].mrph_p = m_num;
    ctx->p_buffer[ctx->p_buffer_num].start = pos;
    ctx->p_buffer[ctx->p_buffer_num].end = pos + new_mrph->length;
    ctx->p_buffer[ctx->p_buffer_num].connect = TRUE;
    if (++(ctx->p_buffer_num) == ctx->process_buffer_max)
	realloc_process_buffer(ctx);
    return TRUE;
}

/*
------------------------------------------------------------------------------
  PROCEDURE: <juman_sent> ��ʸ������ǲ��Ϥ���    by T.Utsuro
------------------------------------------------------------------------------
*/
int juman_sent(JCONTEXT* ctx)
{
    int        i, j, flag;
    int        pos_end, length;
    int        pre_m_buffer_num;
    int        pre_p_buffer_num;
    int        pos, next_pos = 0;
    int	       p_start = 0;

    if (ctx->mrph_buffer_max == 0) {
	ctx->m_buffer = (MRPH *)my_alloc(sizeof(MRPH)*BUFFER_BLOCK_SIZE);
	ctx->m_check_buffer = (int *)my_alloc(sizeof(int)*BUFFER_BLOCK_SIZE);
	ctx->mrph_buffer_max += BUFFER_BLOCK_SIZE;
    }
    if (ctx->process_buffer_max == 0) {
	ctx->p_buffer = (PROCESS_BUFFER *)
	    my_alloc(sizeof(PROCESS_BUFFER)*BUFFER_BLOCK_SIZE);
	ctx->path_buffer = (int *)my_alloc(sizeof(int)*BUFFER_BLOCK_SIZE);
	ctx->match_pbuf = (int *)my_alloc(sizeof(int)*BUFFER_BLOCK_SIZE);
	ctx->process_buffer_max += BUFFER_BLOCK_SIZE;
    }
    ctx->path_mrph_offs = 0;

    if (ctx->pat_search_buffer == NULL) {
      ctx->pat_search_buffer = my_alloc(sizeof(char)*50000);
    }
    if (ctx->chk_connect == NULL) {
      ctx->chk_connect = (CHK_CONNECT_WK*) my_alloc(sizeof(CHK_CONNECT_WK)*MAX_PATHES_WK);
    }
    if (ctx->kigou == NULL) {
      ctx->kigou = (U_CHAR*) my_alloc(sizeof(U_CHAR)*MIDASI_MAX);
    }
    if (ctx->midasi1 == NULL) {
      ctx->midasi1 = (U_CHAR*) my_alloc(sizeof(U_CHAR)*MIDASI_MAX);
    }
    if (ctx->midasi2 == NULL) {
      ctx->midasi2 = (U_CHAR*) my_alloc(sizeof(U_CHAR)*MIDASI_MAX);
    }
    if (ctx->yomi == NULL) {
      ctx->yomi = (U_CHAR*) my_alloc(sizeof(U_CHAR)*MIDASI_MAX);
    }
    
    if (ctx->NormalizedString != NULL
        && ctx->NormalizedString_max < ctx->String_max) {
      my_free(ctx->NormalizedString);
      ctx->NormalizedString = NULL;
      ctx->NormalizedString_max = 0;
    }
    
    if (ctx->NormalizedString == NULL) {
      ctx->NormalizedString_max = ctx->String_max;
      assert(ctx->NormalizedString_max != 0);
      ctx->NormalizedString = (U_CHAR*) my_alloc(ctx->NormalizedString_max);
    }
    
    length = strlen(ctx->String);

    if (length == 0) return FALSE;	/* ���Ԥϥ����å� */

    if (ctx->connect_cache_max == 0)
      ctx->connect_cache_max = 1000;
    if (ctx->connect_cache == NULL)
      ctx->connect_cache
        = my_alloc(sizeof(CONNECT_COST)*ctx->connect_cache_max);
#if 1  /* optim + ensure no uninitialised value is spotted by memcheck */
    memset(ctx->connect_cache, 0, sizeof(CONNECT_COST)*ctx->connect_cache_max);
#else
    for (i = 0; i < ctx->connect_cache_max; i++) {
      ctx->connect_cache[i].p_no = 0;
    }
#endif

    /* ʸƬ���� */
    ctx->p_buffer[0].start = 0;	/* (added RX) */	
    ctx->p_buffer[0].end = 0;		
    ctx->p_buffer[0].path[0] = -1;
    ctx->p_buffer[0].score = 0;	
    ctx->p_buffer[0].mrph_p = 0;
    ctx->p_buffer[0].connect = TRUE;
    ctx->m_buffer[0].hinsi = 0;
    ctx->m_buffer[0].bunrui = 0;
    ctx->m_buffer[0].con_tbl = 0;
    ctx->m_buffer[0].weight = MRPH_DEFAULT_WEIGHT;
    strcpy(ctx->m_buffer[0].midasi , "(ʸƬ)");
    ctx->m_buffer_num = 1;
    ctx->p_buffer_num = 1;

    /* ������ɽ���ؤ��б� */
    strcpy(ctx->NormalizedString, ctx->String);
    for (pos = 0; pos < length; pos+=next_pos) {
        assert(pos >= 0 && pos < ctx->String_max);
	if (ctx->String[pos]&0x80) { /* ���Ѥξ�� */
	    for (i = 0; i < normalized_lowercase; i++) {
		if (!strncmp(ctx->String + pos, lowercase[i], 2)) {
		    ctx->NormalizedString[pos] = uppercase[i][0];
		    ctx->NormalizedString[pos+1] = uppercase[i][1];
		}
	    }
	    next_pos = 2;
	} else {
	    next_pos = 1;
	}
    }

    for (pos = 0; pos < length; pos+=next_pos) {
        assert(pos >= 0 && pos < ctx->String_max);

	p_start = pos_match_process(ctx, pos, p_start);
	if (ctx->match_pbuf[0] >= 0) {
	
	    pre_m_buffer_num = ctx->m_buffer_num;
	    pre_p_buffer_num = ctx->p_buffer_num;
	

        }  /* TEMPORARY */

        /* TEMPORARY: CHECK ME - THIS BLOCK MIGHT BE BETTER PLACED OUTSIDE
           THE CONDITION TEST */

	    if (ctx->String[pos]&0x80) { /* ���Ѥξ�硤�����Ҥ� */
              if (search_all(ctx, pos) == FALSE) return FALSE;
		next_pos = 2;
	    } else {
		next_pos = 1;
	    }

	    if (undef_word(ctx, pos) == FALSE) return FALSE;
    }
    
    /* ʸ������ */
    strcpy(ctx->m_buffer[ctx->m_buffer_num].midasi , "(ʸ��)");
    ctx->m_buffer[ctx->m_buffer_num].hinsi = 0;
    ctx->m_buffer[ctx->m_buffer_num].bunrui = 0;
    ctx->m_buffer[ctx->m_buffer_num].con_tbl = 0;
    ctx->m_buffer[ctx->m_buffer_num].weight = MRPH_DEFAULT_WEIGHT;
    if (++(ctx->m_buffer_num) == ctx->mrph_buffer_max)
	realloc_mrph_buffer(ctx);

    pos_match_process(ctx, pos, p_start);
    if (check_connect(ctx, length, ctx->m_buffer_num-1, 0) == FALSE)
      return FALSE;

    return TRUE;
}
