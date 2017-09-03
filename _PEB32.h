struct _PEB32 {
	unsigned char  InheritedAddressSpace;             //0x000
	unsigned char  ReadImageFileExecOptions;          //0x001
	unsigned char  BeingDebugged;                     //0x002
	union {
		unsigned char  BitField;                          //0x003
		struct {
			char           ImageUsesLargePages       : 1 ;
			char           IsProtectedProcess        : 1 ;
			char           IsImageDynamicallyRelocated : 1 ;
			char           SkipPatchingUser32Forwarders : 1 ;
			char           IsPackagedProcess         : 1 ;
			char           IsAppContainer            : 1 ;
			char           IsProtectedProcessLight   : 1 ;
			char           SpareBits                 : 1 ;
		} ;                    //0x003
	};
	uint32_t       Mutant;                            //0x004
	uint32_t       ImageBaseAddress;                  //0x008
	uint32_t       Ldr;                               //0x00c
	uint32_t       ProcessParameters;                 //0x010
	uint32_t       SubSystemData;                     //0x014
	uint32_t       ProcessHeap;                       //0x018
	uint32_t       FastPebLock;                       //0x01c
	uint32_t       AtlThunkSListPtr;                  //0x020
	uint32_t       IFEOKey;                           //0x024
	union {
		uint32_t       CrossProcessFlags;                 //0x028
		struct {
			int32_t        ProcessInJob              : 1 ;
			int32_t        ProcessInitializing       : 1 ;
			int32_t        ProcessUsingVEH           : 1 ;
			int32_t        ProcessUsingVCH           : 1 ;
			int32_t        ProcessUsingFTH           : 1 ;
			int32_t        ReservedBits0             : 27 ;
		} ;                    //0x028
	};
	union {
		uint32_t       KernelCallbackTable;               //0x02c
		uint32_t       UserSharedInfoPtr;                 //0x02c
	};
	uint32_t       SystemReserved[1];                 //0x030
	uint32_t       AtlThunkSListPtr32;                //0x034
	uint32_t       ApiSetMap;                         //0x038
	uint32_t       TlsExpansionCounter;               //0x03c
	uint32_t       TlsBitmap;                         //0x040
	uint32_t       TlsBitmapBits[2];                  //0x044
	uint32_t       ReadOnlySharedMemoryBase;          //0x04c
	uint32_t       SparePvoid0;                       //0x050
	uint32_t       ReadOnlyStaticServerData;          //0x054
	uint32_t       AnsiCodePageData;                  //0x058
	uint32_t       OemCodePageData;                   //0x05c
	uint32_t       UnicodeCaseTableData;              //0x060
	uint32_t       NumberOfProcessors;                //0x064
	uint32_t       NtGlobalFlag;                      //0x068
	_LARGE_INTEGER CriticalSectionTimeout;            //0x070
	uint32_t       HeapSegmentReserve;                //0x078
	uint32_t       HeapSegmentCommit;                 //0x07c
	uint32_t       HeapDeCommitTotalFreeThreshold;    //0x080
	uint32_t       HeapDeCommitFreeBlockThreshold;    //0x084
	uint32_t       NumberOfHeaps;                     //0x088
	uint32_t       MaximumNumberOfHeaps;              //0x08c
	uint32_t       ProcessHeaps;                      //0x090
	uint32_t       GdiSharedHandleTable;              //0x094
	uint32_t       ProcessStarterHelper;              //0x098
	uint32_t       GdiDCAttributeList;                //0x09c
	uint32_t       LoaderLock;                        //0x0a0
	uint32_t       OSMajorVersion;                    //0x0a4
	uint32_t       OSMinorVersion;                    //0x0a8
	uint16_t       OSBuildNumber;                     //0x0ac
	uint16_t       OSCSDVersion;                      //0x0ae
	uint32_t       OSPlatformId;                      //0x0b0
	uint32_t       ImageSubsystem;                    //0x0b4
	uint32_t       ImageSubsystemMajorVersion;        //0x0b8
	uint32_t       ImageSubsystemMinorVersion;        //0x0bc
	uint32_t       ActiveProcessAffinityMask;         //0x0c0
	uint32_t       GdiHandleBuffer[34];               //0x0c4
	uint32_t       PostProcessInitRoutine;            //0x14c
	uint32_t       TlsExpansionBitmap;                //0x150
	uint32_t       TlsExpansionBitmapBits[32];        //0x154
	uint32_t       SessionId;                         //0x1d4
	_ULARGE_INTEGER AppCompatFlags;                    //0x1d8
	_ULARGE_INTEGER AppCompatFlagsUser;                //0x1e0
	uint32_t       pShimData;                         //0x1e8
	uint32_t       AppCompatInfo;                     //0x1ec
	_STRING32      CSDVersion;                        //0x1f0
	uint32_t       ActivationContextData;             //0x1f8
	uint32_t       ProcessAssemblyStorageMap;         //0x1fc
	uint32_t       SystemDefaultActivationContextData;//0x200
	uint32_t       SystemAssemblyStorageMap;          //0x204
	uint32_t       MinimumStackCommit;                //0x208
	uint32_t       FlsCallback;                       //0x20c
	LIST_ENTRY32   FlsListHead;                       //0x210
	uint32_t       FlsBitmap;                         //0x218
	uint32_t       FlsBitmapBits[4];                  //0x21c
	uint32_t       FlsHighIndex;                      //0x22c
	uint32_t       WerRegistrationData;               //0x230
	uint32_t       WerShipAssertPtr;                  //0x234
	uint32_t       pUnused;                           //0x238
	uint32_t       pImageHeaderHash;                  //0x23c
	union {
		uint32_t       TracingFlags;                      //0x240
		struct {
			int32_t        HeapTracingEnabled        : 1 ;
			int32_t        CritSecTracingEnabled     : 1 ;
			int32_t        LibLoaderTracingEnabled   : 1 ;
			int32_t        SpareTracingBits          : 29 ;
		} ;                    //0x240
	};
	uint64_t       CsrServerReadOnlySharedMemoryBase; //0x248
}  ; 
