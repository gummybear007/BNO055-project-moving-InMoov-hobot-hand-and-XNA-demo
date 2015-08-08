/*
00002    FALCON - The Falcon Programming Language.
00003    FILE: compiler.h
00004 
00005    Main Falcon source compiler.
00006    -------------------------------------------------------------------
00007    Author: Giancarlo Niccolai
00008    Begin: dom giu 6 2004
00009 
00010    -------------------------------------------------------------------
00011    (C) Copyright 2004: the FALCON developers (see list in AUTHORS file)
00012 
00013    See LICENSE file for licensing details.
00014 */
00015 
00016 #ifndef FALCON_COMPILER_H
00017 #define FALCON_COMPILER_H
00018 
00019 #include <falcon/syntree.h>
00020 #include <falcon/error.h>
00021 #include <falcon/common.h>
00022 #include <falcon/string.h>
00023 #include <falcon/module.h>
00024 #include <falcon/genericlist.h>
00025 #include <falcon/basealloc.h>
00026 
00027 extern "C" int flc_src_parse( void *param );
00028 
00029 namespace Falcon
00030 {
00031 
00032 class SrcLexer;
00033 class Stream;
00034 class InteractiveCompiler;
00035 class VMachine;
00036 class ModuleLoader;
00037 
00041 class FALCON_DYN_CLASS AliasMap: public Map
00042 {
00043 public:
00044 
00045    AliasMap();
00046 };
00047 
00048 class FALCON_DYN_CLASS DeclarationContext: public BaseAlloc
00049 {
00050    byte m_value;
00051 public:
00052    DeclarationContext(){ m_value = 0; }
00053    DeclarationContext( const DeclarationContext &dc ) {
00054       m_value = dc.m_value;
00055    }
00056 
00057    DeclarationContext &operator =( const DeclarationContext &other ) {
00058       m_value = other.m_value; return *this;
00059    }
00060 
00061    DeclarationContext &setGlobalQuery() { m_value = 0; return *this; }
00062    DeclarationContext &setQuery() { m_value &= ~0x1; return *this; }
00063    DeclarationContext &setAssign() { m_value |= 0x1; return *this; }
00064    DeclarationContext &setGlobalBody() { m_value &= ~(0x2|0x4|0x8); return *this; }
00065    DeclarationContext &setFunctionBody() { m_value |= 0x2; m_value &= ~(0x4); return *this; }
00066    DeclarationContext &setClassBody() { m_value |= 0x4; m_value &= ~(0x2); return *this; }
00067    DeclarationContext &setStatic() { m_value |= 0x8; return *this; }
00068    DeclarationContext &setNonStatic() { m_value &= ~0x8; return *this; }
00069 
00070 };
00071 
00072 
00080 class FALCON_DYN_CLASS Compiler: public BaseAlloc
00081 {
00082 protected:
00088    typedef enum {
00089       e_dc_global,
00090       e_dc_param,
00091       e_dc_static_func,
00092       e_dc_func_body,
00093       e_dc_static_class,
00094       e_dc_class_body
00095    } t_decl_context;
00096 
00100    Map m_constants;
00101 
00105    Map m_namespaces;
00106 
00107    SourceTree *m_root;
00108 
00109    int m_errors;
00110    int m_optLevel;
00111 
00112    SrcLexer *m_lexer;
00113    Stream *m_stream;
00114 
00116    Module *m_module;
00117 
00118    int64 m_enumId;
00119 
00121    List m_context;
00123    List m_func_ctx;
00124 
00126    List m_contextSet;
00128    List m_loops;
00129 
00139    List m_statementVals;
00140 
00145    List m_functions;
00146 
00150    List m_alias;
00151 
00155    const String *m_staticPrefix;
00156 
00157    int m_lambdaCount;
00158    int m_closureContexts;
00159    int m_tempLine;
00160 
00162    bool m_strict;
00163 
00165    String m_language;
00166 
00168    int64 m_modVersion;
00169 
00170    bool m_defContext;
00171 
00172    bool m_bParsingFtd;
00173 
00174    bool m_bInteractive;
00175 
00176    Error *m_rootError;
00177    InteractiveCompiler *m_metacomp;
00178    VMachine *m_serviceVM;
00179    ModuleLoader *m_serviceLoader;
00180 
00182    String m_searchPath;
00183 
00188    void clear();
00189 
00194    void init();
00195 
00201   void addPredefs();
00202 
00203 public:
00208    Compiler();
00209 
00216    Compiler( Module *mod, Stream *input );
00220    virtual ~Compiler();
00221 
00236    void reset();
00237 
00245    bool compile();
00246 
00255    bool compile( Module *mod, Stream *input );
00256 
00262    void raiseError( int errorNum, int errorLine=0);
00263 
00269    void raiseError( Error *e );
00270 
00278    void raiseContextError( int code, int line, int startLine );
00279    void raiseError( int errorNum, const String &errorp, int errorLine=0);
00280    void addError() { m_errors++; }
00281 
00299    Symbol *searchLocalSymbol( const String *symname, bool bRecurse = false );
00300    Symbol *searchGlobalSymbol( const String *symname );
00301    Symbol *addLocalSymbol( const String *symname, bool parameter );
00302    Symbol *addGlobalSymbol( const String *symname );
00303    Symbol *searchOuterSymbol( const String *symname );
00304 
00310    Symbol *addGlobalVar( const String *symname, VarDef *value );
00311    bool isLocalContext() { return ! m_functions.empty(); }
00312 
00322    const Value *getConstant( const String &name ) {
00323       Value **findp = (Value **) m_constants.find( &name );
00324       if ( findp != 0 )
00325          return *findp;
00326       return 0;
00327    }
00328 
00333    virtual void addLoad( const String &name, bool isFilename ) {
00334       m_module->addDepend( name, false, isFilename );
00335    }
00336 
00337    // Inlines
00338    void addStatement( Statement *stm ) { if ( stm != 0 ) getContextSet()->push_back( stm ); }
00339    void addFunction( Statement *stm ) { if ( stm != 0 ) m_root->functions().push_back( stm ); }
00340    void addClass( Statement *stm ) { if ( stm != 0 ) m_root->classes().push_back( stm ); }
00341    void pushLoop( Statement *stm ) { m_loops.pushBack( stm ); }
00342    void pushFunction( FuncDef *f );
00343    void pushContext( Statement *stm ) { m_context.pushBack( stm ); }
00344    void pushContextSet( StatementList *list ) { m_contextSet.pushBack( list ); }
00345    Statement *getContext() const { if ( m_context.empty() ) return 0; return (Statement *) m_context.back(); }
00346    Statement *getLoop() const { if ( m_loops.empty() ) return 0; return (Statement *) m_loops.back(); }
00347    StatementList *getContextSet() const { if ( m_contextSet.empty() ) return 0; return (StatementList *)m_contextSet.back(); }
00348    FuncDef * getFunction() const { if ( m_functions.empty() ) return 0; return (FuncDef *) m_functions.back(); }
00349    void popLoop() { m_loops.popBack(); }
00350    void popContext() { m_context.popBack(); }
00351    void popContextSet() { m_contextSet.popBack(); }
00352    void popFunction();
00353    void pushFunctionContext( StmtFunction *func ) { m_func_ctx.pushBack( func ); }
00354    void popFunctionContext() { if ( !m_func_ctx.empty() ) m_func_ctx.popBack(); }
00355    StmtFunction *getFunctionContext() const { if ( m_func_ctx.empty() ) return 0; return (StmtFunction*) m_func_ctx.back(); }
00356 
00357    String *addString( const String &str ) { return m_module->addString( str ); }
00358 
00359    SrcLexer *lexer() const { return m_lexer; }
00360    Stream *stream() const { return m_stream; }
00361 
00362    int lambdaCount() const { return m_lambdaCount; }
00363    void incLambdaCount() { m_lambdaCount++; }
00364 
00365    void addNilConstant( const String &name, uint32 line=0 );
00366    void addIntConstant( const String &name, int64 value, uint32 line=0 );
00367    void addNumConstant( const String &name, numeric value, uint32 line=0 );
00368    void addStringConstant( const String &name, const String &value, uint32 line=0 );
00369    void addConstant( const String &name, Value *val, uint32 line=0 );
00370 
00372    void addAttribute( const String &name, Value *val, uint32 line=0 );
00373 
00374 
00375    SourceTree *sourceTree() const { return m_root; }
00376    Module *module() const { return m_module; }
00377 
00378    int errors() const { return m_errors; }
00387    //void include( const char *filename );
00388    //void includePath( const Hstring &incp );
00389 
00397    void defineVal( Value *val );
00398 
00407    void defineVal( ArrayDecl *val );
00408 
00409    Symbol  *globalize( const String *str );
00410 
00412    bool checkLocalUndefined();
00413    void addSymdef( Value *val ) { List *l = (List *) m_statementVals.back(); l->pushBack( val ); }
00414 
00418    const String *staticPrefix() const { return m_staticPrefix; }
00419    void staticPrefix( const String *v ) { m_staticPrefix = v; }
00420 
00429    StmtFunction *buildCtorFor( StmtClass *sym );
00430 
00432    void closeFunction();
00433 
00435    void tempLine( int line ) { m_tempLine = line; }
00436    int tempLine() const { return m_tempLine; }
00437 
00442    void strictMode( bool breq ) { m_strict = breq; }
00443    bool strictMode() const { return m_strict; }
00444 
00446    bool parsingFtd() const;
00447    void parsingFtd( bool b );
00448 
00459    bool setDirective( const String &directive, const String &value, bool bRaise = true );
00460 
00471    bool setDirective( const String &directive, int64 value, bool bRaise = true );
00472 
00473    void defContext( bool ctx ) { m_defContext = ctx; }
00474    bool defContext() const { return m_defContext; }
00475 
00477    Value *closeClosure();
00478    void incClosureContext() { m_closureContexts++; }
00479    void decClosureContext() { m_closureContexts--; }
00480 
00482    void addEnumerator( const String &name, Value *value );
00483 
00487    void addEnumerator( const String &name );
00488 
00489    void resetEnum() { m_enumId = 0; }
00490 
00497    bool isNamespace( const String &symName );
00498 
00505    virtual void addNamespace( const String &nspace, const String &alias, bool full=false, bool filename=false );
00506 
00525    virtual void importSymbols( List *lst, const String *prefix=0, const String *alias=0, bool filename=false );
00526 
00536    virtual Symbol* importAlias( const String *symName, const String *fromMod, const String *alias, bool filename=false );
00537 
00542    void metaCompile( const String &data, int startline );
00543 
00548    VMachine *serviceVM() const { return m_serviceVM; }
00549 
00554    ModuleLoader *serviceLoader() const { return m_serviceLoader; }
00555 
00564    void serviceVM( VMachine *vm ) { m_serviceVM = vm; }
00565 
00574    void serviceLoader(ModuleLoader *l) { m_serviceLoader = l; }
00575 
00588    Error *detachErrors() { Error *e = m_rootError; m_rootError = 0; m_errors = 0; return e; }
00589 
00597    void setInteractive( bool bint ) { m_bInteractive = bint; }
00598 
00600    bool isInteractive() const { return m_bInteractive; }
00601 
00605    const String& searchPath() const { return m_searchPath; }
00606 
00610    void searchPath( const String& path ) { m_searchPath = path; }
00611 };
00612 
00613 } // end of namespace
00614 
00615 #endif
00616 
00617 /* end of compiler.h */