
#ifndef _PP_PROJ_H_
#define _PP_PROJ_H_
//***********************************************************************************
// C header for accessing PMAC Global, CSGlobal, Ptr vars
// _PPScriptMode_ for Pmac Script like access global & csglobal
// global Mypvar - access with "Mypvar"
// global Myparray(32) - access with "Myparray(i)"
// csglobal Myqvar - access with "Myqvar(i)" where "i" is Coord #
// csglobal Myqarray(16) - access with "Myqvar(i,j)" where "j" is index
// _EnumMode_ for Pmac enum data type checking on Set & Get global functions
// Example
// global Mypvar
// csglobal Myqvar
// "SetGlobalVar(Myqvar, data)" will give a compile error because its a csglobal var.
// "SetCSGlobalVar(Mypvar, data)" will give a compile error because its a global var.
//************************************************************************************

#ifdef _PPScriptMode_
enum globalP {_globalP_=-1};
enum globalParray {_globalParray_=-1};
enum csglobalQ {_csglobalQ_=-1};
enum csglobalQarray {_csglobalQarray_=-1};

enum ptrM {_ptrM_=-1
,ADC1X9=8192
,ADC2X9=8193
,ADC1X10=8194
,ADC2X10=8195
,ADC1X11=8196
,ADC2X11=8197
,ADC1X12=8198
,ADC2X12=8199
,DAC1X9=8200
,DAC2X9=8201
,DAC1X10=8202
,DAC2X10=8203
,DAC1X11=8204
,DAC2X11=8205
,DAC1X12=8206
,DAC2X12=8207
,GPIN1X9=8208
,GPIN2X9=8209
,GPIN1X10=8210
,GPIN2X10=8211
,GPIN1X11=8212
,GPIN2X11=8213
,GPIN1X12=8214
,GPIN2X12=8215
,GPIN1X15=8216
,GPIN2X15=8217
,GPIN3X15=8218
,GPIN4X15=8219
,GPIN5X15=8220
,GPIN6X15=8221
,GPIN7X15=8222
,GPIN8X15=8223
,GPIN9X15=8224
,GPIN10X15=8225
,GPIN11X15=8226
,GPIN12X15=8227
,GPIN13X15=8228
,GPIN14X15=8229
,GPIN15X15=8230
,GPIN16X15=8231
,GPIN1X16=8232
,GPIN2X16=8233
,GPIN3X16=8234
,GPIN4X16=8235
,GPIN5X16=8236
,GPIN6X16=8237
,GPIN7X16=8238
,GPIN8X16=8239
,GPIN9X16=8240
,GPIN10X16=8241
,GPIN11X16=8242
,GPIN12X16=8243
,GPIN13X16=8244
,GPIN14X16=8245
,GPIN15X16=8246
,GPIN16X16=8247
,GPOUT1X15=8248
,GPOUT2X15=8249
,GPOUT3X15=8250
,GPOUT4X15=8251
,GPOUT5X15=8252
,GPOUT6X15=8253
,GPOUT7X15=8254
,GPOUT8X15=8255
,GPOUT1X16=8256
,GPOUT2X16=8257
,GPOUT3X16=8258
,GPOUT4X16=8259
,GPOUT5X16=8260
,GPOUT6X16=8261
,GPOUT7X16=8262
,GPOUT8X16=8263};
enum ptrMarray {_ptrMarray_=-1};
#define	PLCMOVEX	pshm->P[8192]
#define	PLCMOVEY	pshm->P[8193]
#define	PLCMOVEZ	pshm->P[8194]
#define	Tdet	pshm->P[8195]
#define	MATRIXROT	pshm->P[8196]
#ifndef _PP_PROJ_HDR_
  void SetEnumGlobalVar(enum globalP var, double data)
  {
    pshm->P[var] = data;
  }

  double GetEnumGlobalVar(enum globalP var)
  {
    return pshm->P[var];
  }

  void SetEnumGlobalArrayVar(enum globalParray var, unsigned index, double data)
  {
    pshm->P[(var + index)%MAX_P] = data;
  }

  double GetEnumGlobalArrayVar(enum globalParray var, unsigned index)
  {
    return pshm->P[(var + index)%MAX_P];
  }

  void SetEnumCSGlobalVar(enum csglobalQ var, unsigned cs, double data)
  {
    pshm->Coord[cs % MAX_COORDS].Q[var] = data;
  }

  double GetEnumCSGlobalVar(enum csglobalQ var, unsigned cs)
  {
    return pshm->Coord[cs % MAX_COORDS].Q[var];
  }

  void SetEnumCSGlobalArrayVar(enum csglobalQarray var, unsigned index, unsigned cs, double data)
  {
    pshm->Coord[cs % MAX_COORDS].Q[(var + index)%MAX_Q] = data;
  }

  double GetEnumCSGlobalArrayVar(enum csglobalQarray var, unsigned index, unsigned cs)
  {
    return pshm->Coord[cs % MAX_COORDS].Q[(var + index)%MAX_Q];
  }

  void SetEnumPtrVar(enum ptrM var, double data)
  {
    im_write(pshm->Mdef + var, data, &pshm->Ldata);
  }

  double GetEnumPtrVar(enum ptrM var)
  {
    return im_read(pshm->Mdef + var, &pshm->Ldata);
  }

  void SetEnumPtrArrayVar(enum ptrMarray var, unsigned index, double data)
  {
    im_write(pshm->Mdef + ((var + index)%MAX_M), data, &pshm->Ldata);
  }

  double GetEnumPtrArrayVar(enum ptrMarray var, unsigned index)
  {
    return im_read(pshm->Mdef + ((var + index)%MAX_M), &pshm->Ldata);
  }

  #define SetGlobalVar(i, x)              SetEnumGlobalVar(i, x)
  #define SetGlobalArrayVar(i, j, x)      SetEnumGlobalArrayVar(i, j, x)
  #define GetGlobalVar(i)                 GetEnumGlobalVar(i)
  #define GetGlobalArrayVar(i, j)         GetEnumGlobalArrayVar(i, j)

  #define SetCSGlobalVar(i, j, x)         SetEnumCSGlobalVar(i, j, x)
  #define SetCSGlobalArrayVar(i, j, k, x) SetEnumCSGlobalArrayVar(i, j, k, x)
  #define GetCSGlobalVar(i, j)            GetEnumCSGlobalVar(i, j)
  #define GetCSGlobalArrayVar(i, j, k)    GetEnumCSGlobalArrayVar(i, j, k)

  #define SetPtrVar(i, x)                 SetEnumPtrVar(i, x)
  #define SetPtrArrayVar(i, j, x)         SetEnumPtrArrayVar(i, j, x)
  #define GetPtrVar(i)                    GetEnumPtrVar(i)
  #define GetPtrArrayVar(i, j)            GetEnumPtrArrayVar(i, j)

#else

  void SetEnumGlobalVar(enum globalP var, double data);
  double GetEnumGlobalVar(enum globalP var);
  void SetEnumGlobalArrayVar(enum globalParray var, unsigned index, double data);
  double GetEnumGlobalArrayVar(enum globalParray var, unsigned index);
  void SetEnumCSGlobalVar(enum csglobalQ var, unsigned cs, double data);
  double GetEnumCSGlobalVar(enum csglobalQ var, unsigned cs);
  void SetEnumCSGlobalArrayVar(enum csglobalQarray var, unsigned index, unsigned cs, double data);
  double GetEnumCSGlobalArrayVar(enum csglobalQarray var, unsigned index, unsigned cs);
  void SetEnumPtrVar(enum ptrM var, double data);
  double GetEnumPtrVar(enum ptrM var);
  void SetEnumPtrArrayVar(enum ptrMarray var, unsigned index, double data);
  double GetEnumPtrArrayVar(enum ptrMarray var, unsigned index);

  #define SetGlobalVar(i, x)              SetEnumGlobalVar(i, x)
  #define SetGlobalArrayVar(i, j, x)      SetEnumGlobalArrayVar(i, j, x)
  #define GetGlobalVar(i)                 GetEnumGlobalVar(i)
  #define GetGlobalArrayVar(i, j)         GetEnumGlobalArrayVar(i, j)

  #define SetCSGlobalVar(i, j, x)         SetEnumCSGlobalVar(i, j, x)
  #define SetCSGlobalArrayVar(i, j, k, x) SetEnumCSGlobalArrayVar(i, j, k, x)
  #define GetCSGlobalVar(i, j)            GetEnumCSGlobalVar(i, j)
  #define GetCSGlobalArrayVar(i, j, k)    GetEnumCSGlobalArrayVar(i, j, k)

  #define SetPtrVar(i, x)                 SetEnumPtrVar(i, x)
  #define SetPtrArrayVar(i, j, x)         SetEnumPtrArrayVar(i, j, x)
  #define GetPtrVar(i)                    GetEnumPtrVar(i)
  #define GetPtrArrayVar(i, j)            GetEnumPtrArrayVar(i, j)

#endif
// end of #ifdef _PPScriptMode_
#else
#ifdef _EnumMode_
enum globalP {_globalP_=-1
,PLCMOVEX=8192
,PLCMOVEY=8193
,PLCMOVEZ=8194
,Tdet=8195
,MATRIXROT=8196};
enum globalParray {_globalParray_=-1};
enum csglobalQ {_csglobalQ_=-1};
enum csglobalQarray {_csglobalQarray_=-1};
enum ptrM {_ptrM_=-1
,ADC1X9=8192
,ADC2X9=8193
,ADC1X10=8194
,ADC2X10=8195
,ADC1X11=8196
,ADC2X11=8197
,ADC1X12=8198
,ADC2X12=8199
,DAC1X9=8200
,DAC2X9=8201
,DAC1X10=8202
,DAC2X10=8203
,DAC1X11=8204
,DAC2X11=8205
,DAC1X12=8206
,DAC2X12=8207
,GPIN1X9=8208
,GPIN2X9=8209
,GPIN1X10=8210
,GPIN2X10=8211
,GPIN1X11=8212
,GPIN2X11=8213
,GPIN1X12=8214
,GPIN2X12=8215
,GPIN1X15=8216
,GPIN2X15=8217
,GPIN3X15=8218
,GPIN4X15=8219
,GPIN5X15=8220
,GPIN6X15=8221
,GPIN7X15=8222
,GPIN8X15=8223
,GPIN9X15=8224
,GPIN10X15=8225
,GPIN11X15=8226
,GPIN12X15=8227
,GPIN13X15=8228
,GPIN14X15=8229
,GPIN15X15=8230
,GPIN16X15=8231
,GPIN1X16=8232
,GPIN2X16=8233
,GPIN3X16=8234
,GPIN4X16=8235
,GPIN5X16=8236
,GPIN6X16=8237
,GPIN7X16=8238
,GPIN8X16=8239
,GPIN9X16=8240
,GPIN10X16=8241
,GPIN11X16=8242
,GPIN12X16=8243
,GPIN13X16=8244
,GPIN14X16=8245
,GPIN15X16=8246
,GPIN16X16=8247
,GPOUT1X15=8248
,GPOUT2X15=8249
,GPOUT3X15=8250
,GPOUT4X15=8251
,GPOUT5X15=8252
,GPOUT6X15=8253
,GPOUT7X15=8254
,GPOUT8X15=8255
,GPOUT1X16=8256
,GPOUT2X16=8257
,GPOUT3X16=8258
,GPOUT4X16=8259
,GPOUT5X16=8260
,GPOUT6X16=8261
,GPOUT7X16=8262
,GPOUT8X16=8263};
enum ptrMarray {_ptrMarray_=-1};
#ifndef _PP_PROJ_HDR_
  void SetEnumGlobalVar(enum globalP var, double data)
  {
    pshm->P[var] = data;
  }

  double GetEnumGlobalVar(enum globalP var)
  {
    return pshm->P[var];
  }

  void SetEnumGlobalArrayVar(enum globalParray var, unsigned index, double data)
  {
    pshm->P[(var + index)%MAX_P] = data;
  }

  double GetEnumGlobalArrayVar(enum globalParray var, unsigned index)
  {
    return pshm->P[(var + index)%MAX_P];
  }

  void SetEnumCSGlobalVar(enum csglobalQ var, unsigned cs, double data)
  {
    pshm->Coord[cs % MAX_COORDS].Q[var] = data;
  }

  double GetEnumCSGlobalVar(enum csglobalQ var, unsigned cs)
  {
    return pshm->Coord[cs % MAX_COORDS].Q[var];
  }

  void SetEnumCSGlobalArrayVar(enum csglobalQarray var, unsigned index, unsigned cs, double data)
  {
    pshm->Coord[cs % MAX_COORDS].Q[(var + index)%MAX_Q] = data;
  }

  double GetEnumCSGlobalArrayVar(enum csglobalQarray var, unsigned index, unsigned cs)
  {
    return pshm->Coord[cs % MAX_COORDS].Q[(var + index)%MAX_Q];
  }

  void SetEnumPtrVar(enum ptrM var, double data)
  {
    im_write(pshm->Mdef + var, data, &pshm->Ldata);
  }

  double GetEnumPtrVar(enum ptrM var)
  {
    return im_read(pshm->Mdef + var, &pshm->Ldata);
  }

  void SetEnumPtrArrayVar(enum ptrMarray var, unsigned index, double data)
  {
    im_write(pshm->Mdef + ((var + index)%MAX_M), data, &pshm->Ldata);
  }

  double GetEnumPtrArrayVar(enum ptrMarray var, unsigned index)
  {
    return im_read(pshm->Mdef + ((var + index)%MAX_M), &pshm->Ldata);
  }

  #define SetGlobalVar(i, x)              SetEnumGlobalVar(i, x)
  #define SetGlobalArrayVar(i, j, x)      SetEnumGlobalArrayVar(i, j, x)
  #define GetGlobalVar(i)                 GetEnumGlobalVar(i)
  #define GetGlobalArrayVar(i, j)         GetEnumGlobalArrayVar(i, j)

  #define SetCSGlobalVar(i, j, x)         SetEnumCSGlobalVar(i, j, x)
  #define SetCSGlobalArrayVar(i, j, k, x) SetEnumCSGlobalArrayVar(i, j, k, x)
  #define GetCSGlobalVar(i, j)            GetEnumCSGlobalVar(i, j)
  #define GetCSGlobalArrayVar(i, j, k)    GetEnumCSGlobalArrayVar(i, j, k)

  #define SetPtrVar(i, x)                 SetEnumPtrVar(i, x)
  #define SetPtrArrayVar(i, j, x)         SetEnumPtrArrayVar(i, j, x)
  #define GetPtrVar(i)                    GetEnumPtrVar(i)
  #define GetPtrArrayVar(i, j)            GetEnumPtrArrayVar(i, j)

#else

  void SetEnumGlobalVar(enum globalP var, double data);
  double GetEnumGlobalVar(enum globalP var);
  void SetEnumGlobalArrayVar(enum globalParray var, unsigned index, double data);
  double GetEnumGlobalArrayVar(enum globalParray var, unsigned index);
  void SetEnumCSGlobalVar(enum csglobalQ var, unsigned cs, double data);
  double GetEnumCSGlobalVar(enum csglobalQ var, unsigned cs);
  void SetEnumCSGlobalArrayVar(enum csglobalQarray var, unsigned index, unsigned cs, double data);
  double GetEnumCSGlobalArrayVar(enum csglobalQarray var, unsigned index, unsigned cs);
  void SetEnumPtrVar(enum ptrM var, double data);
  double GetEnumPtrVar(enum ptrM var);
  void SetEnumPtrArrayVar(enum ptrMarray var, unsigned index, double data);
  double GetEnumPtrArrayVar(enum ptrMarray var, unsigned index);

  #define SetGlobalVar(i, x)              SetEnumGlobalVar(i, x)
  #define SetGlobalArrayVar(i, j, x)      SetEnumGlobalArrayVar(i, j, x)
  #define GetGlobalVar(i)                 GetEnumGlobalVar(i)
  #define GetGlobalArrayVar(i, j)         GetEnumGlobalArrayVar(i, j)

  #define SetCSGlobalVar(i, j, x)         SetEnumCSGlobalVar(i, j, x)
  #define SetCSGlobalArrayVar(i, j, k, x) SetEnumCSGlobalArrayVar(i, j, k, x)
  #define GetCSGlobalVar(i, j)            GetEnumCSGlobalVar(i, j)
  #define GetCSGlobalArrayVar(i, j, k)    GetEnumCSGlobalArrayVar(i, j, k)

  #define SetPtrVar(i, x)                 SetEnumPtrVar(i, x)
  #define SetPtrArrayVar(i, j, x)         SetEnumPtrArrayVar(i, j, x)
  #define GetPtrVar(i)                    GetEnumPtrVar(i)
  #define GetPtrArrayVar(i, j)            GetEnumPtrArrayVar(i, j)

#endif
// end of #ifdef _EnumMode_
#else
// ***** Standard default mode *****
#define ADC1X9 8192
#define ADC2X9 8193
#define ADC1X10 8194
#define ADC2X10 8195
#define ADC1X11 8196
#define ADC2X11 8197
#define ADC1X12 8198
#define ADC2X12 8199
#define DAC1X9 8200
#define DAC2X9 8201
#define DAC1X10 8202
#define DAC2X10 8203
#define DAC1X11 8204
#define DAC2X11 8205
#define DAC1X12 8206
#define DAC2X12 8207
#define GPIN1X9 8208
#define GPIN2X9 8209
#define GPIN1X10 8210
#define GPIN2X10 8211
#define GPIN1X11 8212
#define GPIN2X11 8213
#define GPIN1X12 8214
#define GPIN2X12 8215
#define GPIN1X15 8216
#define GPIN2X15 8217
#define GPIN3X15 8218
#define GPIN4X15 8219
#define GPIN5X15 8220
#define GPIN6X15 8221
#define GPIN7X15 8222
#define GPIN8X15 8223
#define GPIN9X15 8224
#define GPIN10X15 8225
#define GPIN11X15 8226
#define GPIN12X15 8227
#define GPIN13X15 8228
#define GPIN14X15 8229
#define GPIN15X15 8230
#define GPIN16X15 8231
#define GPIN1X16 8232
#define GPIN2X16 8233
#define GPIN3X16 8234
#define GPIN4X16 8235
#define GPIN5X16 8236
#define GPIN6X16 8237
#define GPIN7X16 8238
#define GPIN8X16 8239
#define GPIN9X16 8240
#define GPIN10X16 8241
#define GPIN11X16 8242
#define GPIN12X16 8243
#define GPIN13X16 8244
#define GPIN14X16 8245
#define GPIN15X16 8246
#define GPIN16X16 8247
#define GPOUT1X15 8248
#define GPOUT2X15 8249
#define GPOUT3X15 8250
#define GPOUT4X15 8251
#define GPOUT5X15 8252
#define GPOUT6X15 8253
#define GPOUT7X15 8254
#define GPOUT8X15 8255
#define GPOUT1X16 8256
#define GPOUT2X16 8257
#define GPOUT3X16 8258
#define GPOUT4X16 8259
#define GPOUT5X16 8260
#define GPOUT6X16 8261
#define GPOUT7X16 8262
#define GPOUT8X16 8263
#define PLCMOVEX 8192
#define PLCMOVEY 8193
#define PLCMOVEZ 8194
#define Tdet 8195
#define MATRIXROT 8196
#endif
#endif
#endif //_PP_PROJ_H_
