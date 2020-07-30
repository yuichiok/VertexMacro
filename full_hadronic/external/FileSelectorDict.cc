// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME FileSelectorDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "include/FileSelector.hh"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_FileSelector(void *p = 0);
   static void *newArray_FileSelector(Long_t size, void *p);
   static void delete_FileSelector(void *p);
   static void deleteArray_FileSelector(void *p);
   static void destruct_FileSelector(void *p);
   static void streamer_FileSelector(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FileSelector*)
   {
      ::FileSelector *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FileSelector >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FileSelector", ::FileSelector::Class_Version(), "include/FileSelector.hh", 3,
                  typeid(::FileSelector), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FileSelector::Dictionary, isa_proxy, 16,
                  sizeof(::FileSelector) );
      instance.SetNew(&new_FileSelector);
      instance.SetNewArray(&newArray_FileSelector);
      instance.SetDelete(&delete_FileSelector);
      instance.SetDeleteArray(&deleteArray_FileSelector);
      instance.SetDestructor(&destruct_FileSelector);
      instance.SetStreamerFunc(&streamer_FileSelector);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FileSelector*)
   {
      return GenerateInitInstanceLocal((::FileSelector*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FileSelector*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr FileSelector::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FileSelector::Class_Name()
{
   return "FileSelector";
}

//______________________________________________________________________________
const char *FileSelector::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FileSelector*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FileSelector::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FileSelector*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FileSelector::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FileSelector*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FileSelector::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FileSelector*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void FileSelector::Streamer(TBuffer &R__b)
{
   // Stream an object of class FileSelector.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      { TString R__str; R__str.Streamer(R__b); info_ = R__str.Data(); }
      { TString R__str; R__str.Streamer(R__b); filename_ = R__str.Data(); }
      R__b.CheckByteCount(R__s, R__c, FileSelector::IsA());
   } else {
      R__c = R__b.WriteVersion(FileSelector::IsA(), kTRUE);
      TObject::Streamer(R__b);
      { TString R__str = info_.c_str(); R__str.Streamer(R__b);}
      { TString R__str = filename_.c_str(); R__str.Streamer(R__b);}
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FileSelector(void *p) {
      return  p ? new(p) ::FileSelector : new ::FileSelector;
   }
   static void *newArray_FileSelector(Long_t nElements, void *p) {
      return p ? new(p) ::FileSelector[nElements] : new ::FileSelector[nElements];
   }
   // Wrapper around operator delete
   static void delete_FileSelector(void *p) {
      delete ((::FileSelector*)p);
   }
   static void deleteArray_FileSelector(void *p) {
      delete [] ((::FileSelector*)p);
   }
   static void destruct_FileSelector(void *p) {
      typedef ::FileSelector current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FileSelector(TBuffer &buf, void *obj) {
      ((::FileSelector*)obj)->::FileSelector::Streamer(buf);
   }
} // end of namespace ROOT for class ::FileSelector

namespace {
  void TriggerDictionaryInitialization_FileSelectorDict_Impl() {
    static const char* headers[] = {
"include/FileSelector.hh",
0
    };
    static const char* includePaths[] = {
"/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/root/6.08.06/include",
"/gpfs/home/ilc/yokugawa/macros/semi_leptonic/external/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "FileSelectorDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$include/FileSelector.hh")))  FileSelector;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "FileSelectorDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "include/FileSelector.hh"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"FileSelector", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("FileSelectorDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_FileSelectorDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_FileSelectorDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_FileSelectorDict() {
  TriggerDictionaryInitialization_FileSelectorDict_Impl();
}
