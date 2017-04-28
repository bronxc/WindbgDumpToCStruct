struct _PEB64 {
	unsigned charInheritedAddressSpace;             //0x000
	unsigned charReadImageFileExecOptions;          //0x001
	unsigned charBeingDebugged;                     //0x002
	union {
		unsigned charBitField;                          //0x003
		struct {
			char      ImageUsesLargePages       : 1 ;
			char      IsProtectedProcess        : 1 ;
			char      IsImageDynamicallyRelocated : 1 ;
			char      SkipPatchingUser32Forwarders : 1 ;
			char      IsPackagedProcess         : 1 ;
			char      IsAppContainer            : 1 ;
			char      IsProtectedProcessLight   : 1 ;
			char      SpareBits                 : 1 ;
		} ;                    //0x003
	};
	unsigned charPadding0[4];                       //0x004
	void*     Mutant;                            //0x008
	void*     ImageBaseAddress;                  //0x010
	_PEB_LDR_DATA *Ldr;                               //0x018
	_RTL_USER_PROCESS_PARAMETERS *ProcessParameters;                 //0x020
	void*     SubSystemData;                     //0x028
	void*     ProcessHeap;                       //0x030
	_RTL_CRITICAL_SECTION *FastPebLock;                       //0x038
	void*     AtlThunkSListPtr;                  //0x040
	void*     IFEOKey;                           //0x048
	union {
		uint32_t  CrossProcessFlags;                 //0x050
		struct {
			int32_t   ProcessInJob              : 1 ;
			int32_t   ProcessInitializing       : 1 ;
			int32_t   ProcessUsingVEH           : 1 ;
			int32_t   ProcessUsingVCH           : 1 ;
			int32_t   ProcessUsingFTH           : 1 ;
			int32_t   ReservedBits0             : 27 ;
		} ;                    //0x050
	};
	unsigned charPadding1[4];                       //0x054
	union {
		void*     KernelCallbackTable;               //0x058
		void*     UserSharedInfoPtr;                 //0x058
	};
	uint32_t  SystemReserved[1];                 //0x060
	uint32_t  AtlThunkSListPtr32;                //0x064
	void*     ApiSetMap;                         //0x068
	uint32_t  TlsExpansionCounter;               //0x070
	unsigned charPadding2[4];                       //0x074
	void*     TlsBitmap;                         //0x078
	uint32_t  TlsBitmapBits[2];                  //0x080
	void*     ReadOnlySharedMemoryBase;          //0x088
	void*     SparePvoid0;                       //0x090
	void**    ReadOnlyStaticServerData;          //0x098
	void*     AnsiCodePageData;                  //0x0a0
	void*     OemCodePageData;                   //0x0a8
	void*     UnicodeCaseTableData;              //0x0b0
	uint32_t  NumberOfProcessors;                //0x0b8
	uint32_t  NtGlobalFlag;                      //0x0bc
	_LARGE_INTEGER CriticalSectionTimeout;            //0x0c0
	uint64_t  HeapSegmentReserve;                //0x0c8
	uint64_t  HeapSegmentCommit;                 //0x0d0
	uint64_t  HeapDeCommitTotalFreeThreshold;    //0x0d8
	uint64_t  HeapDeCommitFreeBlockThreshold;    //0x0e0
	uint32_t  NumberOfHeaps;                     //0x0e8
	uint32_t  MaximumNumberOfHeaps;              //0x0ec
	void**    ProcessHeaps;                      //0x0f0
	void*     GdiSharedHandleTable;              //0x0f8
	void*     ProcessStarterHelper;              //0x100
	uint32_t  GdiDCAttributeList;                //0x108
	unsigned charPadding3[4];                       //0x10c
	_RTL_CRITICAL_SECTION *LoaderLock;                        //0x110
	uint32_t  OSMajorVersion;                    //0x118
	uint32_t  OSMinorVersion;                    //0x11c
	uint16_t  OSBuildNumber;                     //0x120
	uint16_t  OSCSDVersion;                      //0x122
	uint32_t  OSPlatformId;                      //0x124
	uint32_t  ImageSubsystem;                    //0x128
	uint32_t  ImageSubsystemMajorVersion;        //0x12c
	uint32_t  ImageSubsystemMinorVersion;        //0x130
	unsigned charPadding4[4];                       //0x134
	uint64_t  ActiveProcessAffinityMask;         //0x138
	uint32_t  GdiHandleBuffer[60];               //0x140
	void*     PostProcessInitRoutine;            //0x230
	void*     TlsExpansionBitmap;                //0x238
	uint32_t  TlsExpansionBitmapBits[32];        //0x240
	uint32_t  SessionId;                         //0x2c0
	unsigned charPadding5[4];                       //0x2c4
	_ULARGE_INTEGER AppCompatFlags;                    //0x2c8
	_ULARGE_INTEGER AppCompatFlagsUser;                //0x2d0
	void*     pShimData;                         //0x2d8
	void*     AppCompatInfo;                     //0x2e0
	_UNICODE_STRING CSDVersion;                        //0x2e8
	_ACTIVATION_CONTEXT_DATA *ActivationContextData;             //0x2f8
	_ASSEMBLY_STORAGE_MAP *ProcessAssemblyStorageMap;         //0x300
	_ACTIVATION_CONTEXT_DATA *SystemDefaultActivationContextData;//0x308
	_ASSEMBLY_STORAGE_MAP *SystemAssemblyStorageMap;          //0x310
	uint64_t  MinimumStackCommit;                //0x318
	_FLS_CALLBACK_INFO *FlsCallback;                       //0x320
	_LIST_ENTRY FlsListHead;                       //0x328
	void*     FlsBitmap;                         //0x338
	uint32_t  FlsBitmapBits[4];                  //0x340
	uint32_t  FlsHighIndex;                      //0x350
	void*     WerRegistrationData;               //0x358
	void*     WerShipAssertPtr;                  //0x360
	void*     pUnused;                           //0x368
	void*     pImageHeaderHash;                  //0x370
	union {
		uint32_t  TracingFlags;                      //0x378
		struct {
			int32_t   HeapTracingEnabled        : 1 ;
			int32_t   CritSecTracingEnabled     : 1 ;
			int32_t   LibLoaderTracingEnabled   : 1 ;
			int32_t   SpareTracingBits          : 29 ;
		} ;                    //0x378
	};
	unsigned charPadding6[4];                       //0x37c
	uint64_t  CsrServerReadOnlySharedMemoryBase; //0x380
}  ; 
