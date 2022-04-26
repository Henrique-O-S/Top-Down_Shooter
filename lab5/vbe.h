#pragma once
  
 #include <stdint.h>
  
 #include <minix/type.h>
  
 #pragma pack(1)
  
 typedef struct {
   /*  Mandatory information for all VBE revisions */
   uint16_t ModeAttributes;   
   uint8_t WinAAttributes;    
   uint8_t WinBAttributes;    
   uint16_t WinGranularity;   
   uint16_t WinSize;          
   uint16_t WinASegment;      
   uint16_t WinBSegment;      
   phys_bytes WinFuncPtr;     
   uint16_t BytesPerScanLine; 
   /* Mandatory information for VBE 1.2 and above */
  
   uint16_t XResolution;       
   uint16_t YResolution;       
   uint8_t XCharSize;          
   uint8_t YCharSize;          
   uint8_t NumberOfPlanes;     
   uint8_t BitsPerPixel;       
   uint8_t NumberOfBanks;      
   uint8_t MemoryModel;        
   uint8_t BankSize;           
   uint8_t NumberOfImagePages; 
   uint8_t Reserved1;          
   /* Direct Color fields (required for direct/6 and YUV/7 memory models) */
  
   uint8_t RedMaskSize;         /* size of direct color red mask in bits */
   uint8_t RedFieldPosition;    /* bit position of lsb of red mask */
   uint8_t GreenMaskSize;       /* size of direct color green mask in bits */
   uint8_t GreenFieldPosition;  /* bit position of lsb of green mask */
   uint8_t BlueMaskSize;        /* size of direct color blue mask in bits */
   uint8_t BlueFieldPosition;   /* bit position of lsb of blue mask */
   uint8_t RsvdMaskSize;        /* size of direct color reserved mask in bits */
   uint8_t RsvdFieldPosition;   /* bit position of lsb of reserved mask */
   uint8_t DirectColorModeInfo; /* direct color mode attributes */
  
   /* Mandatory information for VBE 2.0 and above */
   phys_bytes PhysBasePtr; 
   uint8_t Reserved2[4];   
   uint8_t Reserved3[2];   
   /* Mandatory information for VBE 3.0 and above */
   uint16_t LinBytesPerScanLine;  /* bytes per scan line for linear modes */
   uint8_t BnkNumberOfImagePages; /* number of images for banked modes */
   uint8_t LinNumberOfImagePages; /* number of images for linear modes */
   uint8_t LinRedMaskSize;        /* size of direct color red mask (linear modes) */
   uint8_t LinRedFieldPosition;   /* bit position of lsb of red mask (linear modes) */
   uint8_t LinGreenMaskSize;      /* size of direct color green mask (linear modes) */
   uint8_t LinGreenFieldPosition; /* bit position of lsb of green mask (linear  modes) */
   uint8_t LinBlueMaskSize;       /* size of direct color blue mask (linear modes) */
   uint8_t LinBlueFieldPosition;  /* bit position of lsb of blue mask (linear modes ) */
   uint8_t LinRsvdMaskSize;       /* size of direct color reserved mask (linear modes) */
   uint8_t LinRsvdFieldPosition;  /* bit position of lsb of reserved mask (linear modes) */
   uint32_t MaxPixelClock;        /* maximum pixel clock (in Hz) for graphics mode */
   uint8_t Reserved4[190];        /* remainder of ModeInfoBlock */
 } vbe_mode_info_t;
  
 #pragma options align = reset
  
 typedef uint8_t BCD; 
 typedef struct vg_vbe_contr_info {
   char VBESignature[4];    
   BCD VBEVersion[2];       
   char *OEMString;         
   uint16_t *VideoModeList; 
   uint32_t TotalMemory;    
   char *OEMVendorNamePtr;  
   char *OEMProductNamePtr; 
   char *OEMProductRevPtr;  
 } vg_vbe_contr_info_t;
  
 int(vbe_get_mode_info)(uint16_t mode, vbe_mode_info_t *vmi_p);
  