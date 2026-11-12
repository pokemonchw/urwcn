Offline PE disassembly; Windows x86 3.89.1 build 26139145. All windows start at known function/instruction boundaries.

/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe:     file format pei-i386


Disassembly of section .text:

004fbd80 <.text+0xfad80>:
  4fbd80:	55                   	push   ebp
  4fbd81:	8b ec                	mov    ebp,esp
  4fbd83:	83 e4 f8             	and    esp,0xfffffff8
  4fbd86:	81 ec 1c 04 00 00    	sub    esp,0x41c
  4fbd8c:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  4fbd91:	33 c4                	xor    eax,esp
  4fbd93:	89 84 24 18 04 00 00 	mov    DWORD PTR [esp+0x418],eax
  4fbd9a:	53                   	push   ebx
  4fbd9b:	8b d9                	mov    ebx,ecx
  4fbd9d:	89 5c 24 0c          	mov    DWORD PTR [esp+0xc],ebx
  4fbda1:	56                   	push   esi
  4fbda2:	57                   	push   edi
  4fbda3:	8b fa                	mov    edi,edx
  4fbda5:	83 fb 01             	cmp    ebx,0x1
  4fbda8:	75 17                	jne    0x4fbdc1
  4fbdaa:	8b c1                	mov    eax,ecx
  4fbdac:	5f                   	pop    edi
  4fbdad:	5e                   	pop    esi
  4fbdae:	5b                   	pop    ebx
  4fbdaf:	8b 8c 24 18 04 00 00 	mov    ecx,DWORD PTR [esp+0x418]
  4fbdb6:	33 cc                	xor    ecx,esp
  4fbdb8:	e8 f1 e2 08 00       	call   0x58a0ae
  4fbdbd:	8b e5                	mov    esp,ebp
  4fbdbf:	5d                   	pop    ebp
  4fbdc0:	c3                   	ret
  4fbdc1:	33 d2                	xor    edx,edx
  4fbdc3:	b9 04 a7 5a 00       	mov    ecx,0x5aa704
  4fbdc8:	e8 73 07 01 00       	call   0x50c540
  4fbdcd:	b8 09 00 00 00       	mov    eax,0x9
  4fbdd2:	8b f3                	mov    esi,ebx
  4fbdd4:	3b d8                	cmp    ebx,eax
  4fbdd6:	53                   	push   ebx
  4fbdd7:	0f 4f f0             	cmovg  esi,eax
  4fbdda:	8d 44 24 24          	lea    eax,[esp+0x24]
  4fbdde:	68 10 a7 5a 00       	push   0x5aa710
  4fbde3:	50                   	push   eax
  4fbde4:	89 74 24 1c          	mov    DWORD PTR [esp+0x1c],esi
  4fbde8:	e8 e3 52 f0 ff       	call   0x4010d0
  4fbded:	83 c4 0c             	add    esp,0xc
  4fbdf0:	85 ff                	test   edi,edi
  4fbdf2:	74 0f                	je     0x4fbe03
  4fbdf4:	53                   	push   ebx
  4fbdf5:	8d 44 24 24          	lea    eax,[esp+0x24]
  4fbdf9:	57                   	push   edi
  4fbdfa:	50                   	push   eax
  4fbdfb:	e8 d0 52 f0 ff       	call   0x4010d0
  4fbe00:	83 c4 0c             	add    esp,0xc
  4fbe03:	8b 7d 08             	mov    edi,DWORD PTR [ebp+0x8]
  4fbe06:	8d 44 24 20          	lea    eax,[esp+0x20]
  4fbe0a:	8b 55 0c             	mov    edx,DWORD PTR [ebp+0xc]
  4fbe0d:	8b cf                	mov    ecx,edi
  4fbe0f:	6a 00                	push   0x0
  4fbe11:	6a 08                	push   0x8
  4fbe13:	50                   	push   eax
  4fbe14:	6a 37                	push   0x37
  4fbe16:	68 27 01 00 00       	push   0x127
  4fbe1b:	e8 50 a4 01 00       	call   0x516270
  4fbe20:	8b 45 0c             	mov    eax,DWORD PTR [ebp+0xc]
  4fbe23:	83 c4 14             	add    esp,0x14
  4fbe26:	83 c0 02             	add    eax,0x2
  4fbe29:	6a 64                	push   0x64
  4fbe2b:	6a 32                	push   0x32
  4fbe2d:	68 2c 01 00 00       	push   0x12c
  4fbe32:	50                   	push   eax
  4fbe33:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4fbe38:	57                   	push   edi
  4fbe39:	68 ff 00 00 00       	push   0xff
  4fbe3e:	68 ff 00 00 00       	push   0xff
  4fbe43:	68 ff 00 00 00       	push   0xff
  4fbe48:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4fbe4b:	ff 15 f8 c1 58 00    	call   DWORD PTR ds:0x58c1f8
  4fbe51:	83 c4 10             	add    esp,0x10
  4fbe54:	ba 16 c6 58 00       	mov    edx,0x58c616
  4fbe59:	8b c8                	mov    ecx,eax
  4fbe5b:	e8 30 39 fd ff       	call   0x4cf790
  4fbe60:	8b 45 0c             	mov    eax,DWORD PTR [ebp+0xc]
  4fbe63:	8d 4f 05             	lea    ecx,[edi+0x5]
  4fbe66:	83 c4 14             	add    esp,0x14
  4fbe69:	89 4c 24 1c          	mov    DWORD PTR [esp+0x1c],ecx
  4fbe6d:	83 c0 14             	add    eax,0x14
  4fbe70:	c7 05 9c 4a 35 06 01 	mov    DWORD PTR ds:0x6354a9c,0x1
  4fbe77:	00 00 00 
  4fbe7a:	8b d1                	mov    edx,ecx
  4fbe7c:	c7 05 a0 4a 35 06 01 	mov    DWORD PTR ds:0x6354aa0,0x1
  4fbe83:	00 00 00 
  4fbe86:	b9 0d 00 00 00       	mov    ecx,0xd
  4fbe8b:	68 28 a7 5a 00       	push   0x5aa728
  4fbe90:	50                   	push   eax
  4fbe91:	e8 5a 3c fd ff       	call   0x4cfaf0
  4fbe96:	8b 45 0c             	mov    eax,DWORD PTR [ebp+0xc]
  4fbe99:	8d 97 fe 00 00 00    	lea    edx,[edi+0xfe]
  4fbe9f:	83 c0 22             	add    eax,0x22
  4fbea2:	b9 1b 00 00 00       	mov    ecx,0x1b
  4fbea7:	68 b8 50 5a 00       	push   0x5a50b8
  4fbeac:	50                   	push   eax
  4fbead:	89 44 24 28          	mov    DWORD PTR [esp+0x28],eax
  4fbeb1:	e8 3a 3c fd ff       	call   0x4cfaf0
  4fbeb6:	a1 34 4a 35 06       	mov    eax,ds:0x6354a34
  4fbebb:	83 c4 10             	add    esp,0x10
  4fbebe:	a3 bc 4a 35 06       	mov    ds:0x6354abc,eax
  4fbec3:	c6 05 53 bc 8f 01 01 	mov    BYTE PTR ds:0x18fbc53,0x1
  4fbeca:	85 f6                	test   esi,esi
  4fbecc:	7e 5c                	jle    0x4fbf2a
  4fbece:	8b 5c 24 10          	mov    ebx,DWORD PTR [esp+0x10]
  4fbed2:	8d 04 b6             	lea    eax,[esi+esi*4]
  4fbed5:	8b 75 08             	mov    esi,DWORD PTR [ebp+0x8]
  4fbed8:	bf 31 00 00 00       	mov    edi,0x31
  4fbedd:	c1 e0 02             	shl    eax,0x2
  4fbee0:	2b f0                	sub    esi,eax
  4fbee2:	81 c6 22 01 00 00    	add    esi,0x122
  4fbee8:	8d 47 d0             	lea    eax,[edi-0x30]
  4fbeeb:	50                   	push   eax
  4fbeec:	8d 44 24 24          	lea    eax,[esp+0x24]
  4fbef0:	68 bc 03 59 00       	push   0x5903bc
  4fbef5:	50                   	push   eax
  4fbef6:	e8 d5 51 f0 ff       	call   0x4010d0
  4fbefb:	83 c4 0c             	add    esp,0xc
  4fbefe:	8d 44 24 20          	lea    eax,[esp+0x20]
  4fbf02:	8b d6                	mov    edx,esi
  4fbf04:	8b cf                	mov    ecx,edi
  4fbf06:	50                   	push   eax
  4fbf07:	8b 45 0c             	mov    eax,DWORD PTR [ebp+0xc]
  4fbf0a:	83 c0 14             	add    eax,0x14
  4fbf0d:	50                   	push   eax
  4fbf0e:	e8 dd 3b fd ff       	call   0x4cfaf0
  4fbf13:	83 c4 08             	add    esp,0x8
  4fbf16:	83 c6 14             	add    esi,0x14
  4fbf19:	47                   	inc    edi
  4fbf1a:	83 eb 01             	sub    ebx,0x1
  4fbf1d:	75 c9                	jne    0x4fbee8
  4fbf1f:	8b 5c 24 14          	mov    ebx,DWORD PTR [esp+0x14]
  4fbf23:	8b 74 24 10          	mov    esi,DWORD PTR [esp+0x10]
  4fbf27:	8b 7d 08             	mov    edi,DWORD PTR [ebp+0x8]
  4fbf2a:	3b de                	cmp    ebx,esi
  4fbf2c:	7e 19                	jle    0x4fbf47
  4fbf2e:	68 34 a7 5a 00       	push   0x5aa734
  4fbf33:	ff 74 24 1c          	push   DWORD PTR [esp+0x1c]
  4fbf37:	8d 57 05             	lea    edx,[edi+0x5]
  4fbf3a:	b9 20 00 00 00       	mov    ecx,0x20
  4fbf3f:	e8 ac 3b fd ff       	call   0x4cfaf0
  4fbf44:	83 c4 08             	add    esp,0x8
  4fbf47:	ba 16 c6 58 00       	mov    edx,0x58c616
  4fbf4c:	b9 1b 00 00 00       	mov    ecx,0x1b
  4fbf51:	e8 3a 3a fd ff       	call   0x4cf990
  4fbf56:	e8 c5 51 fd ff       	call   0x4d1120
  4fbf5b:	83 f8 64             	cmp    eax,0x64
  4fbf5e:	7c 04                	jl     0x4fbf64
  4fbf60:	33 c9                	xor    ecx,ecx
  4fbf62:	eb 14                	jmp    0x4fbf78
  4fbf64:	85 c0                	test   eax,eax
  4fbf66:	79 04                	jns    0x4fbf6c
  4fbf68:	33 c9                	xor    ecx,ecx
  4fbf6a:	eb 0c                	jmp    0x4fbf78
  4fbf6c:	69 c0 e8 00 00 00    	imul   eax,eax,0xe8
  4fbf72:	8b 88 d8 ef 34 06    	mov    ecx,DWORD PTR [eax+0x634efd8]
  4fbf78:	8d 41 f3             	lea    eax,[ecx-0xd]
  4fbf7b:	83 f8 2c             	cmp    eax,0x2c
  4fbf7e:	77 d6                	ja     0x4fbf56
  4fbf80:	0f b6 80 2c c1 4f 00 	movzx  eax,BYTE PTR [eax+0x4fc12c]
  4fbf87:	ff 24 85 18 c1 4f 00 	jmp    DWORD PTR [eax*4+0x4fc118]
  4fbf8e:	53                   	push   ebx
  4fbf8f:	8d 44 24 24          	lea    eax,[esp+0x24]
  4fbf93:	68 10 a7 5a 00       	push   0x5aa710
  4fbf98:	50                   	push   eax
  4fbf99:	e8 32 51 f0 ff       	call   0x4010d0
  4fbf9e:	8b 5d 0c             	mov    ebx,DWORD PTR [ebp+0xc]
  4fbfa1:	8d 44 24 2c          	lea    eax,[esp+0x2c]
  4fbfa5:	83 c4 0c             	add    esp,0xc
  4fbfa8:	8b d3                	mov    edx,ebx
  4fbfaa:	8b cf                	mov    ecx,edi
  4fbfac:	6a 00                	push   0x0
  4fbfae:	6a 08                	push   0x8
  4fbfb0:	50                   	push   eax
  4fbfb1:	6a 37                	push   0x37
  4fbfb3:	68 27 01 00 00       	push   0x127
  4fbfb8:	e8 b3 a2 01 00       	call   0x516270
  4fbfbd:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4fbfc2:	8d 73 1c             	lea    esi,[ebx+0x1c]
  4fbfc5:	83 c4 14             	add    esp,0x14
  4fbfc8:	8d 5f 05             	lea    ebx,[edi+0x5]
  4fbfcb:	8d 7e 04             	lea    edi,[esi+0x4]
  4fbfce:	6a 54                	push   0x54
  4fbfd0:	68 fc 00 00 00       	push   0xfc
  4fbfd5:	68 fc 00 00 00       	push   0xfc
  4fbfda:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4fbfdd:	ff 15 f8 c1 58 00    	call   DWORD PTR ds:0x58c1f8
  4fbfe3:	8b 4c 24 2c          	mov    ecx,DWORD PTR [esp+0x2c]
  4fbfe7:	83 c4 0c             	add    esp,0xc
  4fbfea:	8b d6                	mov    edx,esi
  4fbfec:	6a 0f                	push   0xf
  4fbfee:	68 1d 01 00 00       	push   0x11d
  4fbff3:	e8 88 54 01 00       	call   0x511480
  4fbff8:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4fbffd:	83 c4 0c             	add    esp,0xc
  4fc000:	8b 35 f8 c1 58 00    	mov    esi,DWORD PTR ds:0x58c1f8
  4fc006:	68 de 00 00 00       	push   0xde
  4fc00b:	68 c4 00 00 00       	push   0xc4
  4fc010:	68 b0 00 00 00       	push   0xb0
  4fc015:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4fc018:	ff d6                	call   esi
  4fc01a:	6a 01                	push   0x1
  4fc01c:	50                   	push   eax
  4fc01d:	68 c0 c8 58 00       	push   0x58c8c0
  4fc022:	8b d7                	mov    edx,edi
  4fc024:	8d 4b 05             	lea    ecx,[ebx+0x5]
  4fc027:	e8 74 25 01 00       	call   0x50e5a0
  4fc02c:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4fc031:	83 c4 1c             	add    esp,0x1c
  4fc034:	6a 01                	push   0x1
  4fc036:	68 ff 00 00 00       	push   0xff
  4fc03b:	68 ff 00 00 00       	push   0xff
  4fc040:	68 ff 00 00 00       	push   0xff
  4fc045:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4fc048:	ff d6                	call   esi
  4fc04a:	8b 55 0c             	mov    edx,DWORD PTR [ebp+0xc]
  4fc04d:	83 c4 10             	add    esp,0x10
  4fc050:	8b 4d 08             	mov    ecx,DWORD PTR [ebp+0x8]
  4fc053:	83 c1 0a             	add    ecx,0xa
  4fc056:	50                   	push   eax
  4fc057:	68 44 a7 5a 00       	push   0x5aa744
  4fc05c:	8d 52 1f             	lea    edx,[edx+0x1f]
  4fc05f:	e8 3c 25 01 00       	call   0x50e5a0
  4fc064:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4fc069:	83 c4 0c             	add    esp,0xc
  4fc06c:	68 de 00 00 00       	push   0xde
  4fc071:	68 c4 00 00 00       	push   0xc4
  4fc076:	68 b0 00 00 00       	push   0xb0
  4fc07b:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4fc07e:	ff d6                	call   esi
  4fc080:	83 c4 10             	add    esp,0x10
  4fc083:	ba 0a 00 00 00       	mov    edx,0xa
  4fc088:	8b c8                	mov    ecx,eax
  4fc08a:	e8 21 35 01 00       	call   0x50f5b0
  4fc08f:	8d 54 24 20          	lea    edx,[esp+0x20]
  4fc093:	2b d0                	sub    edx,eax
  4fc095:	8a 08                	mov    cl,BYTE PTR [eax]
  4fc097:	8d 40 01             	lea    eax,[eax+0x1]
  4fc09a:	88 4c 02 ff          	mov    BYTE PTR [edx+eax*1-0x1],cl
  4fc09e:	84 c9                	test   cl,cl
  4fc0a0:	75 f3                	jne    0x4fc095
  4fc0a2:	8d 44 24 20          	lea    eax,[esp+0x20]
  4fc0a6:	50                   	push   eax
  4fc0a7:	ff 15 74 c3 58 00    	call   DWORD PTR ds:0x58c374
  4fc0ad:	8b 5c 24 18          	mov    ebx,DWORD PTR [esp+0x18]
  4fc0b1:	83 c4 04             	add    esp,0x4
  4fc0b4:	8b f0                	mov    esi,eax
  4fc0b6:	eb 0b                	jmp    0x4fc0c3
  4fc0b8:	33 f6                	xor    esi,esi
  4fc0ba:	eb 07                	jmp    0x4fc0c3
  4fc0bc:	8b f3                	mov    esi,ebx
  4fc0be:	eb 03                	jmp    0x4fc0c3
  4fc0c0:	8d 71 d0             	lea    esi,[ecx-0x30]
  4fc0c3:	b9 04 a7 5a 00       	mov    ecx,0x5aa704
  4fc0c8:	e8 c3 05 01 00       	call   0x50c690
  4fc0cd:	b9 04 a7 5a 00       	mov    ecx,0x5aa704
  4fc0d2:	e8 e9 03 01 00       	call   0x50c4c0
  4fc0d7:	c6 05 53 bc 8f 01 00 	mov    BYTE PTR ds:0x18fbc53,0x0
  4fc0de:	83 fe 01             	cmp    esi,0x1
  4fc0e1:	7c 1b                	jl     0x4fc0fe
  4fc0e3:	3b f3                	cmp    esi,ebx
  4fc0e5:	7f 17                	jg     0x4fc0fe
  4fc0e7:	8b c6                	mov    eax,esi
  4fc0e9:	5f                   	pop    edi
  4fc0ea:	5e                   	pop    esi
  4fc0eb:	5b                   	pop    ebx
  4fc0ec:	8b 8c 24 18 04 00 00 	mov    ecx,DWORD PTR [esp+0x418]
  4fc0f3:	33 cc                	xor    ecx,esp
  4fc0f5:	e8 b4 df 08 00       	call   0x58a0ae
  4fc0fa:	8b e5                	mov    esp,ebp
  4fc0fc:	5d                   	pop    ebp
  4fc0fd:	c3                   	ret
  4fc0fe:	8b 8c 24 24 04 00 00 	mov    ecx,DWORD PTR [esp+0x424]
  4fc105:	33 c0                	xor    eax,eax
  4fc107:	5f                   	pop    edi
  4fc108:	5e                   	pop    esi
  4fc109:	5b                   	pop    ebx
  4fc10a:	33 cc                	xor    ecx,esp
  4fc10c:	e8 9d df 08 00       	call   0x58a0ae
  4fc111:	8b e5                	mov    esp,ebp
  4fc113:	5d                   	pop    ebp
  4fc114:	c3                   	ret

/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe:     file format pei-i386


Disassembly of section .text:

004fc160 <.text+0xfb160>:
  4fc160:	55                   	push   ebp
  4fc161:	8b ec                	mov    ebp,esp
  4fc163:	81 ec 08 04 00 00    	sub    esp,0x408
  4fc169:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  4fc16e:	33 c5                	xor    eax,ebp
  4fc170:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  4fc173:	0f 10 05 54 a7 5a 00 	movups xmm0,XMMWORD PTR ds:0x5aa754
  4fc17a:	a1 6c a7 5a 00       	mov    eax,ds:0x5aa76c
  4fc17f:	8b ca                	mov    ecx,edx
  4fc181:	89 85 10 fc ff ff    	mov    DWORD PTR [ebp-0x3f0],eax
  4fc187:	8d 95 f8 fb ff ff    	lea    edx,[ebp-0x408]
  4fc18d:	a0 70 a7 5a 00       	mov    al,ds:0x5aa770
  4fc192:	0f 11 85 f8 fb ff ff 	movups XMMWORD PTR [ebp-0x408],xmm0
  4fc199:	68 1f 02 00 00       	push   0x21f
  4fc19e:	f3 0f 7e 05 64 a7 5a 	movq   xmm0,QWORD PTR ds:0x5aa764
  4fc1a5:	00 
  4fc1a6:	68 f4 01 00 00       	push   0x1f4
  4fc1ab:	66 0f d6 85 08 fc ff 	movq   QWORD PTR [ebp-0x3f8],xmm0
  4fc1b2:	ff 
  4fc1b3:	88 85 14 fc ff ff    	mov    BYTE PTR [ebp-0x3ec],al
  4fc1b9:	e8 c2 fb ff ff       	call   0x4fbd80
  4fc1be:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  4fc1c1:	83 c4 08             	add    esp,0x8
  4fc1c4:	33 cd                	xor    ecx,ebp
  4fc1c6:	e8 e3 de 08 00       	call   0x58a0ae
  4fc1cb:	8b e5                	mov    esp,ebp
  4fc1cd:	5d                   	pop    ebp
  4fc1ce:	c3                   	ret

/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe:     file format pei-i386


Disassembly of section .text:

004fc1d0 <.text+0xfb1d0>:
  4fc1d0:	55                   	push   ebp
  4fc1d1:	8b ec                	mov    ebp,esp
  4fc1d3:	83 e4 f8             	and    esp,0xfffffff8
  4fc1d6:	83 ec 7c             	sub    esp,0x7c
  4fc1d9:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  4fc1de:	33 c4                	xor    eax,esp
  4fc1e0:	89 44 24 78          	mov    DWORD PTR [esp+0x78],eax
  4fc1e4:	53                   	push   ebx
  4fc1e5:	56                   	push   esi
  4fc1e6:	57                   	push   edi
  4fc1e7:	8b fa                	mov    edi,edx
  4fc1e9:	8b d9                	mov    ebx,ecx
  4fc1eb:	89 7c 24 14          	mov    DWORD PTR [esp+0x14],edi
  4fc1ef:	83 ff 01             	cmp    edi,0x1
  4fc1f2:	75 14                	jne    0x4fc208
  4fc1f4:	8b c2                	mov    eax,edx
  4fc1f6:	5f                   	pop    edi
  4fc1f7:	5e                   	pop    esi
  4fc1f8:	5b                   	pop    ebx
  4fc1f9:	8b 4c 24 78          	mov    ecx,DWORD PTR [esp+0x78]
  4fc1fd:	33 cc                	xor    ecx,esp
  4fc1ff:	e8 aa de 08 00       	call   0x58a0ae
  4fc204:	8b e5                	mov    esp,ebp
  4fc206:	5d                   	pop    ebp
  4fc207:	c3                   	ret
  4fc208:	33 d2                	xor    edx,edx
  4fc20a:	b9 04 a7 5a 00       	mov    ecx,0x5aa704
  4fc20f:	e8 2c 03 01 00       	call   0x50c540
  4fc214:	b8 09 00 00 00       	mov    eax,0x9
  4fc219:	8b f7                	mov    esi,edi
  4fc21b:	3b f8                	cmp    edi,eax
  4fc21d:	57                   	push   edi
  4fc21e:	0f 4f f0             	cmovg  esi,eax
  4fc221:	8d 44 24 1c          	lea    eax,[esp+0x1c]
  4fc225:	68 10 a7 5a 00       	push   0x5aa710
  4fc22a:	50                   	push   eax
  4fc22b:	89 74 24 1c          	mov    DWORD PTR [esp+0x1c],esi
  4fc22f:	e8 9c 4e f0 ff       	call   0x4010d0
  4fc234:	83 c4 0c             	add    esp,0xc
  4fc237:	8d 44 24 18          	lea    eax,[esp+0x18]
  4fc23b:	ba 1f 02 00 00       	mov    edx,0x21f
  4fc240:	6a 08                	push   0x8
  4fc242:	50                   	push   eax
  4fc243:	6a 37                	push   0x37
  4fc245:	68 27 01 00 00       	push   0x127
  4fc24a:	8d 4a d5             	lea    ecx,[edx-0x2b]
  4fc24d:	e8 1e 9c 01 00       	call   0x515e70
  4fc252:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4fc257:	83 c4 10             	add    esp,0x10
  4fc25a:	6a 64                	push   0x64
  4fc25c:	6a 32                	push   0x32
  4fc25e:	68 2c 01 00 00       	push   0x12c
  4fc263:	68 21 02 00 00       	push   0x221
  4fc268:	68 f4 01 00 00       	push   0x1f4
  4fc26d:	68 ff 00 00 00       	push   0xff
  4fc272:	68 ff 00 00 00       	push   0xff
  4fc277:	68 ff 00 00 00       	push   0xff
  4fc27c:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4fc27f:	ff 15 f8 c1 58 00    	call   DWORD PTR ds:0x58c1f8
  4fc285:	83 c4 10             	add    esp,0x10
  4fc288:	ba 16 c6 58 00       	mov    edx,0x58c616
  4fc28d:	8b c8                	mov    ecx,eax
  4fc28f:	e8 fc 34 fd ff       	call   0x4cf790
  4fc294:	83 c4 14             	add    esp,0x14
  4fc297:	c7 05 9c 4a 35 06 01 	mov    DWORD PTR ds:0x6354a9c,0x1
  4fc29e:	00 00 00 
  4fc2a1:	ba f9 01 00 00       	mov    edx,0x1f9
  4fc2a6:	c7 05 a0 4a 35 06 01 	mov    DWORD PTR ds:0x6354aa0,0x1
  4fc2ad:	00 00 00 
  4fc2b0:	b9 0d 00 00 00       	mov    ecx,0xd
  4fc2b5:	68 28 a7 5a 00       	push   0x5aa728
  4fc2ba:	68 33 02 00 00       	push   0x233
  4fc2bf:	e8 2c 38 fd ff       	call   0x4cfaf0
  4fc2c4:	68 b8 50 5a 00       	push   0x5a50b8
  4fc2c9:	68 41 02 00 00       	push   0x241
  4fc2ce:	ba f2 02 00 00       	mov    edx,0x2f2
  4fc2d3:	b9 1b 00 00 00       	mov    ecx,0x1b
  4fc2d8:	e8 13 38 fd ff       	call   0x4cfaf0
  4fc2dd:	a1 34 4a 35 06       	mov    eax,ds:0x6354a34
  4fc2e2:	83 c4 10             	add    esp,0x10
  4fc2e5:	a3 bc 4a 35 06       	mov    ds:0x6354abc,eax
  4fc2ea:	c6 05 53 bc 8f 01 01 	mov    BYTE PTR ds:0x18fbc53,0x1
  4fc2f1:	85 f6                	test   esi,esi
  4fc2f3:	7e 67                	jle    0x4fc35c
  4fc2f5:	8b 4c 24 10          	mov    ecx,DWORD PTR [esp+0x10]
  4fc2f9:	bf 16 03 00 00       	mov    edi,0x316
  4fc2fe:	be 01 00 00 00       	mov    esi,0x1
  4fc303:	89 4c 24 0c          	mov    DWORD PTR [esp+0xc],ecx
  4fc307:	8d 04 89             	lea    eax,[ecx+ecx*4]
  4fc30a:	c1 e0 02             	shl    eax,0x2
  4fc30d:	2b f8                	sub    edi,eax
  4fc30f:	8b c1                	mov    eax,ecx
  4fc311:	85 db                	test   ebx,ebx
  4fc313:	74 04                	je     0x4fc319
  4fc315:	3b f3                	cmp    esi,ebx
  4fc317:	7c 2e                	jl     0x4fc347
  4fc319:	56                   	push   esi
  4fc31a:	8d 44 24 1c          	lea    eax,[esp+0x1c]
  4fc31e:	68 bc 03 59 00       	push   0x5903bc
  4fc323:	50                   	push   eax
  4fc324:	e8 a7 4d f0 ff       	call   0x4010d0
  4fc329:	83 c4 0c             	add    esp,0xc
  4fc32c:	8d 44 24 18          	lea    eax,[esp+0x18]
  4fc330:	8d 4e 30             	lea    ecx,[esi+0x30]
  4fc333:	8b d7                	mov    edx,edi
  4fc335:	50                   	push   eax
  4fc336:	68 33 02 00 00       	push   0x233
  4fc33b:	e8 b0 37 fd ff       	call   0x4cfaf0
  4fc340:	8b 44 24 14          	mov    eax,DWORD PTR [esp+0x14]
  4fc344:	83 c4 08             	add    esp,0x8
  4fc347:	83 c7 14             	add    edi,0x14
  4fc34a:	46                   	inc    esi
  4fc34b:	83 e8 01             	sub    eax,0x1
  4fc34e:	89 44 24 0c          	mov    DWORD PTR [esp+0xc],eax
  4fc352:	75 bd                	jne    0x4fc311
  4fc354:	8b 7c 24 14          	mov    edi,DWORD PTR [esp+0x14]
  4fc358:	8b 74 24 10          	mov    esi,DWORD PTR [esp+0x10]
  4fc35c:	3b fe                	cmp    edi,esi
  4fc35e:	7e 1c                	jle    0x4fc37c
  4fc360:	68 34 a7 5a 00       	push   0x5aa734
  4fc365:	68 41 02 00 00       	push   0x241
  4fc36a:	ba f9 01 00 00       	mov    edx,0x1f9
  4fc36f:	b9 20 00 00 00       	mov    ecx,0x20
  4fc374:	e8 77 37 fd ff       	call   0x4cfaf0
  4fc379:	83 c4 08             	add    esp,0x8
  4fc37c:	ba 16 c6 58 00       	mov    edx,0x58c616
  4fc381:	b9 1b 00 00 00       	mov    ecx,0x1b
  4fc386:	e8 05 36 fd ff       	call   0x4cf990
  4fc38b:	0f 1f 44 00 00       	nop    DWORD PTR [eax+eax*1+0x0]
  4fc390:	e8 8b 4d fd ff       	call   0x4d1120
  4fc395:	83 f8 64             	cmp    eax,0x64
  4fc398:	7c 04                	jl     0x4fc39e
  4fc39a:	33 c9                	xor    ecx,ecx
  4fc39c:	eb 14                	jmp    0x4fc3b2
  4fc39e:	85 c0                	test   eax,eax
  4fc3a0:	79 04                	jns    0x4fc3a6
  4fc3a2:	33 c9                	xor    ecx,ecx
  4fc3a4:	eb 0c                	jmp    0x4fc3b2
  4fc3a6:	69 c0 e8 00 00 00    	imul   eax,eax,0xe8
  4fc3ac:	8b 88 d8 ef 34 06    	mov    ecx,DWORD PTR [eax+0x634efd8]
  4fc3b2:	8d 41 f3             	lea    eax,[ecx-0xd]
  4fc3b5:	83 f8 2c             	cmp    eax,0x2c
  4fc3b8:	77 d6                	ja     0x4fc390
  4fc3ba:	0f b6 80 70 c5 4f 00 	movzx  eax,BYTE PTR [eax+0x4fc570]
  4fc3c1:	ff 24 85 5c c5 4f 00 	jmp    DWORD PTR [eax*4+0x4fc55c]
  4fc3c8:	57                   	push   edi
  4fc3c9:	8d 44 24 1c          	lea    eax,[esp+0x1c]
  4fc3cd:	68 10 a7 5a 00       	push   0x5aa710
  4fc3d2:	50                   	push   eax
  4fc3d3:	e8 f8 4c f0 ff       	call   0x4010d0
  4fc3d8:	83 c4 0c             	add    esp,0xc
  4fc3db:	8d 44 24 18          	lea    eax,[esp+0x18]
  4fc3df:	ba 1f 02 00 00       	mov    edx,0x21f
  4fc3e4:	6a 08                	push   0x8
  4fc3e6:	50                   	push   eax
  4fc3e7:	6a 37                	push   0x37
  4fc3e9:	68 27 01 00 00       	push   0x127
  4fc3ee:	8d 4a d5             	lea    ecx,[edx-0x2b]
  4fc3f1:	e8 7a 9a 01 00       	call   0x515e70
  4fc3f6:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4fc3fb:	8b 35 f8 c1 58 00    	mov    esi,DWORD PTR ds:0x58c1f8
  4fc401:	6a 54                	push   0x54
  4fc403:	68 fc 00 00 00       	push   0xfc
  4fc408:	68 fc 00 00 00       	push   0xfc
  4fc40d:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4fc410:	ff d6                	call   esi
  4fc412:	83 c4 1c             	add    esp,0x1c
  4fc415:	ba 3b 02 00 00       	mov    edx,0x23b
  4fc41a:	6a 0f                	push   0xf
  4fc41c:	68 1d 01 00 00       	push   0x11d
  4fc421:	8d 4a be             	lea    ecx,[edx-0x42]
  4fc424:	e8 57 50 01 00       	call   0x511480
  4fc429:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4fc42e:	83 c4 0c             	add    esp,0xc
  4fc431:	68 de 00 00 00       	push   0xde
  4fc436:	68 c4 00 00 00       	push   0xc4
  4fc43b:	68 b0 00 00 00       	push   0xb0
  4fc440:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4fc443:	ff d6                	call   esi
  4fc445:	ba 3f 02 00 00       	mov    edx,0x23f
  4fc44a:	6a 01                	push   0x1
  4fc44c:	50                   	push   eax
  4fc44d:	68 c0 c8 58 00       	push   0x58c8c0
  4fc452:	8d 4a bf             	lea    ecx,[edx-0x41]
  4fc455:	e8 46 21 01 00       	call   0x50e5a0
  4fc45a:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4fc45f:	83 c4 1c             	add    esp,0x1c
  4fc462:	6a 01                	push   0x1
  4fc464:	68 ff 00 00 00       	push   0xff
  4fc469:	68 ff 00 00 00       	push   0xff
  4fc46e:	68 ff 00 00 00       	push   0xff
  4fc473:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4fc476:	ff d6                	call   esi
  4fc478:	83 c4 10             	add    esp,0x10
  4fc47b:	ba 3e 02 00 00       	mov    edx,0x23e
  4fc480:	50                   	push   eax
  4fc481:	68 44 a7 5a 00       	push   0x5aa744
  4fc486:	8d 4a c0             	lea    ecx,[edx-0x40]
  4fc489:	e8 12 21 01 00       	call   0x50e5a0
  4fc48e:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4fc493:	83 c4 0c             	add    esp,0xc
  4fc496:	68 de 00 00 00       	push   0xde
  4fc49b:	68 c4 00 00 00       	push   0xc4
  4fc4a0:	68 b0 00 00 00       	push   0xb0
  4fc4a5:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4fc4a8:	ff d6                	call   esi
  4fc4aa:	83 c4 10             	add    esp,0x10
  4fc4ad:	ba 0a 00 00 00       	mov    edx,0xa
  4fc4b2:	8b c8                	mov    ecx,eax
  4fc4b4:	e8 f7 30 01 00       	call   0x50f5b0
  4fc4b9:	8d 54 24 18          	lea    edx,[esp+0x18]
  4fc4bd:	2b d0                	sub    edx,eax
  4fc4bf:	90                   	nop
  4fc4c0:	8a 08                	mov    cl,BYTE PTR [eax]
  4fc4c2:	8d 40 01             	lea    eax,[eax+0x1]
  4fc4c5:	88 4c 02 ff          	mov    BYTE PTR [edx+eax*1-0x1],cl
  4fc4c9:	84 c9                	test   cl,cl
  4fc4cb:	75 f3                	jne    0x4fc4c0
  4fc4cd:	8d 44 24 18          	lea    eax,[esp+0x18]
  4fc4d1:	50                   	push   eax
  4fc4d2:	ff 15 74 c3 58 00    	call   DWORD PTR ds:0x58c374
  4fc4d8:	83 c4 04             	add    esp,0x4
  4fc4db:	8b f0                	mov    esi,eax
  4fc4dd:	eb 0b                	jmp    0x4fc4ea
  4fc4df:	33 f6                	xor    esi,esi
  4fc4e1:	eb 07                	jmp    0x4fc4ea
  4fc4e3:	8b f7                	mov    esi,edi
  4fc4e5:	eb 03                	jmp    0x4fc4ea
  4fc4e7:	8d 71 d0             	lea    esi,[ecx-0x30]
  4fc4ea:	b9 04 a7 5a 00       	mov    ecx,0x5aa704
  4fc4ef:	e8 9c 01 01 00       	call   0x50c690
  4fc4f4:	b9 04 a7 5a 00       	mov    ecx,0x5aa704
  4fc4f9:	e8 c2 ff 00 00       	call   0x50c4c0
  4fc4fe:	c6 05 53 bc 8f 01 00 	mov    BYTE PTR ds:0x18fbc53,0x0
  4fc505:	83 fe 01             	cmp    esi,0x1
  4fc508:	7c 3a                	jl     0x4fc544
  4fc50a:	3b f7                	cmp    esi,edi
  4fc50c:	7f 36                	jg     0x4fc544
  4fc50e:	3b f3                	cmp    esi,ebx
  4fc510:	7d 1e                	jge    0x4fc530
  4fc512:	53                   	push   ebx
  4fc513:	8d 44 24 1c          	lea    eax,[esp+0x1c]
  4fc517:	8b f3                	mov    esi,ebx
  4fc519:	68 74 a7 5a 00       	push   0x5aa774
  4fc51e:	50                   	push   eax
  4fc51f:	e8 ac 4b f0 ff       	call   0x4010d0
  4fc524:	83 c4 0c             	add    esp,0xc
  4fc527:	8d 4c 24 18          	lea    ecx,[esp+0x18]
  4fc52b:	e8 e0 9f ff ff       	call   0x4f6510
  4fc530:	8b c6                	mov    eax,esi
  4fc532:	5f                   	pop    edi
  4fc533:	5e                   	pop    esi
  4fc534:	5b                   	pop    ebx
  4fc535:	8b 4c 24 78          	mov    ecx,DWORD PTR [esp+0x78]
  4fc539:	33 cc                	xor    ecx,esp
  4fc53b:	e8 6e db 08 00       	call   0x58a0ae
  4fc540:	8b e5                	mov    esp,ebp
  4fc542:	5d                   	pop    ebp
  4fc543:	c3                   	ret
  4fc544:	8b 8c 24 84 00 00 00 	mov    ecx,DWORD PTR [esp+0x84]
  4fc54b:	33 c0                	xor    eax,eax
  4fc54d:	5f                   	pop    edi
  4fc54e:	5e                   	pop    esi
  4fc54f:	5b                   	pop    ebx
  4fc550:	33 cc                	xor    ecx,esp
  4fc552:	e8 57 db 08 00       	call   0x58a0ae
  4fc557:	8b e5                	mov    esp,ebp
  4fc559:	5d                   	pop    ebp
  4fc55a:	c3                   	ret

/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe:     file format pei-i386


Disassembly of section .text:

0050f5b0 <.text+0x10e5b0>:
  50f5b0:	55                   	push   ebp
  50f5b1:	8b ec                	mov    ebp,esp
  50f5b3:	81 ec bc 00 00 00    	sub    esp,0xbc
  50f5b9:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  50f5be:	33 c5                	xor    eax,ebp
  50f5c0:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  50f5c3:	53                   	push   ebx
  50f5c4:	56                   	push   esi
  50f5c5:	8b 35 b4 1c 5c 0a    	mov    esi,DWORD PTR ds:0xa5c1cb4
  50f5cb:	8b d9                	mov    ebx,ecx
  50f5cd:	57                   	push   edi
  50f5ce:	8b 3d 3c bb 5b 06    	mov    edi,DWORD PTR ds:0x65bbb3c
  50f5d4:	8b ce                	mov    ecx,esi
  50f5d6:	89 95 4c ff ff ff    	mov    DWORD PTR [ebp-0xb4],edx
  50f5dc:	89 9d 54 ff ff ff    	mov    DWORD PTR [ebp-0xac],ebx
  50f5e2:	89 b5 5c ff ff ff    	mov    DWORD PTR [ebp-0xa4],esi
  50f5e8:	8d 57 03             	lea    edx,[edi+0x3]
  50f5eb:	89 bd 48 ff ff ff    	mov    DWORD PTR [ebp-0xb8],edi
  50f5f1:	e8 9a c6 ff ff       	call   0x50bc90
  50f5f6:	6a 64                	push   0x64
  50f5f8:	6a 00                	push   0x0
  50f5fa:	68 a8 b9 89 0a       	push   0xa89b9a8
  50f5ff:	89 85 58 ff ff ff    	mov    DWORD PTR [ebp-0xa8],eax
  50f605:	e8 56 b8 07 00       	call   0x58ae60
  50f60a:	83 c4 0c             	add    esp,0xc
  50f60d:	f6 05 58 ba 5b 06 01 	test   BYTE PTR ds:0x65bba58,0x1
  50f614:	74 63                	je     0x50f679
  50f616:	33 c9                	xor    ecx,ecx
  50f618:	0f 1f 84 00 00 00 00 	nop    DWORD PTR [eax+eax*1+0x0]
  50f61f:	00 
  50f620:	8a 81 60 ba 5b 06    	mov    al,BYTE PTR [ecx+0x65bba60]
  50f626:	8d 49 01             	lea    ecx,[ecx+0x1]
  50f629:	88 81 a7 b9 89 0a    	mov    BYTE PTR [ecx+0xa89b9a7],al
  50f62f:	84 c0                	test   al,al
  50f631:	75 ed                	jne    0x50f620
  50f633:	b9 a8 b9 89 0a       	mov    ecx,0xa89b9a8
  50f638:	8d 51 01             	lea    edx,[ecx+0x1]
  50f63b:	0f 1f 44 00 00       	nop    DWORD PTR [eax+eax*1+0x0]
  50f640:	8a 01                	mov    al,BYTE PTR [ecx]
  50f642:	41                   	inc    ecx
  50f643:	84 c0                	test   al,al
  50f645:	75 f9                	jne    0x50f640
  50f647:	ff b5 58 ff ff ff    	push   DWORD PTR [ebp-0xa8]
  50f64d:	2b ca                	sub    ecx,edx
  50f64f:	89 75 80             	mov    DWORD PTR [ebp-0x80],esi
  50f652:	89 7d 84             	mov    DWORD PTR [ebp-0x7c],edi
  50f655:	c7 45 8c 0b 00 00 00 	mov    DWORD PTR [ebp-0x74],0xb
  50f65c:	8d 04 cd 05 00 00 00 	lea    eax,[ecx*8+0x5]
  50f663:	89 45 88             	mov    DWORD PTR [ebp-0x78],eax
  50f666:	8d 45 80             	lea    eax,[ebp-0x80]
  50f669:	50                   	push   eax
  50f66a:	ff 35 10 bb 5b 06    	push   DWORD PTR ds:0x65bbb10
  50f670:	ff 15 e8 c1 58 00    	call   DWORD PTR ds:0x58c1e8
  50f676:	83 c4 0c             	add    esp,0xc
  50f679:	6a 64                	push   0x64
  50f67b:	6a 00                	push   0x0
  50f67d:	68 60 ba 5b 06       	push   0x65bba60
  50f682:	e8 d9 b7 07 00       	call   0x58ae60
  50f687:	8d 4f 01             	lea    ecx,[edi+0x1]
  50f68a:	8b c7                	mov    eax,edi
  50f68c:	2b c1                	sub    eax,ecx
  50f68e:	83 c4 0c             	add    esp,0xc
  50f691:	83 c0 0b             	add    eax,0xb
  50f694:	89 85 50 ff ff ff    	mov    DWORD PTR [ebp-0xb0],eax
  50f69a:	66 0f 1f 44 00 00    	nop    WORD PTR [eax+eax*1+0x0]
  50f6a0:	6a 00                	push   0x0
  50f6a2:	53                   	push   ebx
  50f6a3:	68 a8 b9 89 0a       	push   0xa89b9a8
  50f6a8:	8b d7                	mov    edx,edi
  50f6aa:	8b ce                	mov    ecx,esi
  50f6ac:	e8 ef ee ff ff       	call   0x50e5a0
  50f6b1:	8b 35 b4 1c 5c 0a    	mov    esi,DWORD PTR ds:0xa5c1cb4
  50f6b7:	83 c4 0c             	add    esp,0xc
  50f6ba:	8b d7                	mov    edx,edi
  50f6bc:	8b ce                	mov    ecx,esi
  50f6be:	6a 00                	push   0x0
  50f6c0:	53                   	push   ebx
  50f6c1:	68 04 c9 5a 00       	push   0x5ac904
  50f6c6:	e8 d5 ee ff ff       	call   0x50e5a0
  50f6cb:	83 c4 0c             	add    esp,0xc
  50f6ce:	83 3d 5c ba 5b 06 00 	cmp    DWORD PTR ds:0x65bba5c,0x0
  50f6d5:	75 42                	jne    0x50f719
  50f6d7:	e8 b4 b8 ff ff       	call   0x50af90
  50f6dc:	83 3d d8 bc 5b 06 00 	cmp    DWORD PTR ds:0x65bbcd8,0x0
  50f6e3:	74 17                	je     0x50f6fc
  50f6e5:	e8 56 09 00 00       	call   0x510040
  50f6ea:	a1 d8 bc 5b 06       	mov    eax,ds:0x65bbcd8
  50f6ef:	33 c9                	xor    ecx,ecx
  50f6f1:	83 f8 02             	cmp    eax,0x2
  50f6f4:	0f 44 c1             	cmove  eax,ecx
  50f6f7:	a3 d8 bc 5b 06       	mov    ds:0x65bbcd8,eax
  50f6fc:	e8 bf bc ff ff       	call   0x50b3c0
  50f701:	83 3d 54 1c 5c 0a 00 	cmp    DWORD PTR ds:0xa5c1c54,0x0
  50f708:	75 0f                	jne    0x50f719
  50f70a:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  50f710:	ff 15 7c c2 58 00    	call   DWORD PTR ds:0x58c27c
  50f716:	83 c4 04             	add    esp,0x4
  50f719:	e8 d2 44 fc ff       	call   0x4d3bf0
  50f71e:	6a 64                	push   0x64
  50f720:	8b d8                	mov    ebx,eax
  50f722:	8d 45 90             	lea    eax,[ebp-0x70]
  50f725:	6a 00                	push   0x0
  50f727:	50                   	push   eax
  50f728:	e8 33 b7 07 00       	call   0x58ae60
  50f72d:	83 c4 0c             	add    esp,0xc
  50f730:	81 fb 24 04 00 00    	cmp    ebx,0x424
  50f736:	75 07                	jne    0x50f73f
  50f738:	bb 99 00 00 00       	mov    ebx,0x99
  50f73d:	eb 0e                	jmp    0x50f74d
  50f73f:	81 fb 23 04 00 00    	cmp    ebx,0x423
  50f745:	b8 8e 00 00 00       	mov    eax,0x8e
  50f74a:	0f 44 d8             	cmove  ebx,eax
  50f74d:	ff b5 58 ff ff ff    	push   DWORD PTR [ebp-0xa8]
  50f753:	8d 47 01             	lea    eax,[edi+0x1]
  50f756:	89 75 80             	mov    DWORD PTR [ebp-0x80],esi
  50f759:	89 45 84             	mov    DWORD PTR [ebp-0x7c],eax
  50f75c:	8b 85 50 ff ff ff    	mov    eax,DWORD PTR [ebp-0xb0]
  50f762:	89 45 8c             	mov    DWORD PTR [ebp-0x74],eax
  50f765:	8d 45 80             	lea    eax,[ebp-0x80]
  50f768:	50                   	push   eax
  50f769:	ff 35 10 bb 5b 06    	push   DWORD PTR ds:0x65bbb10
  50f76f:	c7 45 88 09 00 00 00 	mov    DWORD PTR [ebp-0x78],0x9
  50f776:	ff 15 e8 c1 58 00    	call   DWORD PTR ds:0x58c1e8
  50f77c:	83 c4 0c             	add    esp,0xc
  50f77f:	83 fb 08             	cmp    ebx,0x8
  50f782:	0f 85 86 00 00 00    	jne    0x50f80e
  50f788:	b9 a8 b9 89 0a       	mov    ecx,0xa89b9a8
  50f78d:	8d 51 01             	lea    edx,[ecx+0x1]
  50f790:	8a 01                	mov    al,BYTE PTR [ecx]
  50f792:	41                   	inc    ecx
  50f793:	84 c0                	test   al,al
  50f795:	75 f9                	jne    0x50f790
  50f797:	8b b5 5c ff ff ff    	mov    esi,DWORD PTR [ebp-0xa4]
  50f79d:	2b ca                	sub    ecx,edx
  50f79f:	74 73                	je     0x50f814
  50f7a1:	ff b5 58 ff ff ff    	push   DWORD PTR [ebp-0xa8]
  50f7a7:	8d 04 cd 05 00 00 00 	lea    eax,[ecx*8+0x5]
  50f7ae:	89 b5 70 ff ff ff    	mov    DWORD PTR [ebp-0x90],esi
  50f7b4:	89 85 78 ff ff ff    	mov    DWORD PTR [ebp-0x88],eax
  50f7ba:	8d 85 70 ff ff ff    	lea    eax,[ebp-0x90]
  50f7c0:	50                   	push   eax
  50f7c1:	ff 35 10 bb 5b 06    	push   DWORD PTR ds:0x65bbb10
  50f7c7:	89 bd 74 ff ff ff    	mov    DWORD PTR [ebp-0x8c],edi
  50f7cd:	c7 85 7c ff ff ff 0b 	mov    DWORD PTR [ebp-0x84],0xb
  50f7d4:	00 00 00 
  50f7d7:	ff 15 e8 c1 58 00    	call   DWORD PTR ds:0x58c1e8
  50f7dd:	b9 a8 b9 89 0a       	mov    ecx,0xa89b9a8
  50f7e2:	83 c4 0c             	add    esp,0xc
  50f7e5:	8d 51 01             	lea    edx,[ecx+0x1]
  50f7e8:	8a 01                	mov    al,BYTE PTR [ecx]
  50f7ea:	41                   	inc    ecx
  50f7eb:	84 c0                	test   al,al
  50f7ed:	75 f9                	jne    0x50f7e8
  50f7ef:	2b ca                	sub    ecx,edx
  50f7f1:	49                   	dec    ecx
  50f7f2:	83 f9 64             	cmp    ecx,0x64
  50f7f5:	0f 83 49 01 00 00    	jae    0x50f944
  50f7fb:	88 81 a8 b9 89 0a    	mov    BYTE PTR [ecx+0xa89b9a8],al
  50f801:	8b 85 54 ff ff ff    	mov    eax,DWORD PTR [ebp-0xac]
  50f807:	a3 68 10 61 0a       	mov    ds:0xa611068,eax
  50f80c:	eb 06                	jmp    0x50f814
  50f80e:	8b b5 5c ff ff ff    	mov    esi,DWORD PTR [ebp-0xa4]
  50f814:	f6 05 58 ba 5b 06 02 	test   BYTE PTR ds:0x65bba58,0x2
  50f81b:	74 15                	je     0x50f832
  50f81d:	83 fb 2a             	cmp    ebx,0x2a
  50f820:	0f 84 a2 00 00 00    	je     0x50f8c8
  50f826:	81 fb fc 03 00 00    	cmp    ebx,0x3fc
  50f82c:	0f 84 96 00 00 00    	je     0x50f8c8
  50f832:	83 fb 1b             	cmp    ebx,0x1b
  50f835:	75 09                	jne    0x50f840
  50f837:	66 89 1d a8 b9 89 0a 	mov    WORD PTR ds:0xa89b9a8,bx
  50f83e:	eb 63                	jmp    0x50f8a3
  50f840:	8d 43 e0             	lea    eax,[ebx-0x20]
  50f843:	83 f8 79             	cmp    eax,0x79
  50f846:	77 5b                	ja     0x50f8a3
  50f848:	b8 a8 b9 89 0a       	mov    eax,0xa89b9a8
  50f84d:	8d 50 01             	lea    edx,[eax+0x1]
  50f850:	8a 08                	mov    cl,BYTE PTR [eax]
  50f852:	40                   	inc    eax
  50f853:	84 c9                	test   cl,cl
  50f855:	75 f9                	jne    0x50f850
  50f857:	2b c2                	sub    eax,edx
  50f859:	3b 85 4c ff ff ff    	cmp    eax,DWORD PTR [ebp-0xb4]
  50f85f:	73 42                	jae    0x50f8a3
  50f861:	53                   	push   ebx
  50f862:	8d 45 90             	lea    eax,[ebp-0x70]
  50f865:	68 dc d6 58 00       	push   0x58d6dc
  50f86a:	50                   	push   eax
  50f86b:	e8 60 18 ef ff       	call   0x4010d0
  50f870:	8d 55 90             	lea    edx,[ebp-0x70]
  50f873:	83 c4 0c             	add    esp,0xc
  50f876:	8b f2                	mov    esi,edx
  50f878:	8a 02                	mov    al,BYTE PTR [edx]
  50f87a:	42                   	inc    edx
  50f87b:	84 c0                	test   al,al
  50f87d:	75 f9                	jne    0x50f878
  50f87f:	bf a8 b9 89 0a       	mov    edi,0xa89b9a8
  50f884:	2b d6                	sub    edx,esi
  50f886:	4f                   	dec    edi
  50f887:	8a 47 01             	mov    al,BYTE PTR [edi+0x1]
  50f88a:	47                   	inc    edi
  50f88b:	84 c0                	test   al,al
  50f88d:	75 f8                	jne    0x50f887
  50f88f:	8b ca                	mov    ecx,edx
  50f891:	c1 e9 02             	shr    ecx,0x2
  50f894:	f3 a5                	rep movs DWORD PTR es:[edi],DWORD PTR ds:[esi]
  50f896:	8b ca                	mov    ecx,edx
  50f898:	83 e1 03             	and    ecx,0x3
  50f89b:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
  50f89d:	8b bd 48 ff ff ff    	mov    edi,DWORD PTR [ebp-0xb8]
  50f8a3:	33 c9                	xor    ecx,ecx
  50f8a5:	83 fb 1b             	cmp    ebx,0x1b
  50f8a8:	0f 95 c1             	setne  cl
  50f8ab:	33 c0                	xor    eax,eax
  50f8ad:	83 fb 0d             	cmp    ebx,0xd
  50f8b0:	0f 95 c0             	setne  al
  50f8b3:	85 c8                	test   eax,ecx
  50f8b5:	74 6d                	je     0x50f924
  50f8b7:	8b 9d 54 ff ff ff    	mov    ebx,DWORD PTR [ebp-0xac]
  50f8bd:	8b b5 5c ff ff ff    	mov    esi,DWORD PTR [ebp-0xa4]
  50f8c3:	e9 d8 fd ff ff       	jmp    0x50f6a0
  50f8c8:	b9 a8 b9 89 0a       	mov    ecx,0xa89b9a8
  50f8cd:	8d 51 01             	lea    edx,[ecx+0x1]
  50f8d0:	8a 01                	mov    al,BYTE PTR [ecx]
  50f8d2:	41                   	inc    ecx
  50f8d3:	84 c0                	test   al,al
  50f8d5:	75 f9                	jne    0x50f8d0
  50f8d7:	ff b5 58 ff ff ff    	push   DWORD PTR [ebp-0xa8]
  50f8dd:	2b ca                	sub    ecx,edx
  50f8df:	89 b5 60 ff ff ff    	mov    DWORD PTR [ebp-0xa0],esi
  50f8e5:	89 bd 64 ff ff ff    	mov    DWORD PTR [ebp-0x9c],edi
  50f8eb:	c7 85 6c ff ff ff 0b 	mov    DWORD PTR [ebp-0x94],0xb
  50f8f2:	00 00 00 
  50f8f5:	8d 04 cd 05 00 00 00 	lea    eax,[ecx*8+0x5]
  50f8fc:	8d 8d 60 ff ff ff    	lea    ecx,[ebp-0xa0]
  50f902:	89 85 68 ff ff ff    	mov    DWORD PTR [ebp-0x98],eax
  50f908:	51                   	push   ecx
  50f909:	ff 35 10 bb 5b 06    	push   DWORD PTR ds:0x65bbb10
  50f90f:	ff 15 e8 c1 58 00    	call   DWORD PTR ds:0x58c1e8
  50f915:	b9 2a 00 00 00       	mov    ecx,0x2a
  50f91a:	83 c4 0c             	add    esp,0xc
  50f91d:	66 89 0d a8 b9 89 0a 	mov    WORD PTR ds:0xa89b9a8,cx
  50f924:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  50f927:	b8 a8 b9 89 0a       	mov    eax,0xa89b9a8
  50f92c:	5f                   	pop    edi
  50f92d:	5e                   	pop    esi
  50f92e:	33 cd                	xor    ecx,ebp
  50f930:	c7 05 58 ba 5b 06 00 	mov    DWORD PTR ds:0x65bba58,0x0
  50f937:	00 00 00 
  50f93a:	5b                   	pop    ebx
  50f93b:	e8 6e a7 07 00       	call   0x58a0ae
  50f940:	8b e5                	mov    esp,ebp
  50f942:	5d                   	pop    ebp
  50f943:	c3                   	ret
  50f944:	e8 99 a8 07 00       	call   0x58a1e2

Caller 00455060, CALL 004572a7, last 35 disassembly lines from function entry:
  457226:	8b b0 e0 ef 34 06    	mov    esi,DWORD PTR [eax+0x634efe0]
  45722c:	03 b0 e8 ef 34 06    	add    esi,DWORD PTR [eax+0x634efe8]
  457232:	83 3d dc e5 34 06 00 	cmp    DWORD PTR ds:0x634e5dc,0x0
  457239:	8b b8 e4 ef 34 06    	mov    edi,DWORD PTR [eax+0x634efe4]
  45723f:	75 09                	jne    0x45724a
  457241:	83 3d f4 4d 35 06 00 	cmp    DWORD PTR ds:0x6354df4,0x0
  457248:	74 50                	je     0x45729a
  45724a:	ff 15 84 c2 58 00    	call   DWORD PTR ds:0x58c284
  457250:	a8 03                	test   al,0x3
  457252:	74 46                	je     0x45729a
  457254:	8b bb b4 ed 6e 00    	mov    edi,DWORD PTR [ebx+0x6eedb4]
  45725a:	33 d2                	xor    edx,edx
  45725c:	8b b3 b0 ed 6e 00    	mov    esi,DWORD PTR [ebx+0x6eedb0]
  457262:	b9 b0 30 6f 00       	mov    ecx,0x6f30b0
  457267:	89 bb b8 ed 6e 00    	mov    DWORD PTR [ebx+0x6eedb8],edi
  45726d:	0f 1f 00             	nop    DWORD PTR [eax]
  457270:	8b 01                	mov    eax,DWORD PTR [ecx]
  457272:	3b c6                	cmp    eax,esi
  457274:	75 13                	jne    0x457289
  457276:	85 c0                	test   eax,eax
  457278:	74 0f                	je     0x457289
  45727a:	8b 41 fc             	mov    eax,DWORD PTR [ecx-0x4]
  45727d:	3b 83 ac ed 6e 00    	cmp    eax,DWORD PTR [ebx+0x6eedac]
  457283:	0f 84 5e 00 00 00    	je     0x4572e7
  457289:	83 c1 20             	add    ecx,0x20
  45728c:	42                   	inc    edx
  45728d:	81 f9 30 6f 6f 00    	cmp    ecx,0x6f6f30
  457293:	7c db                	jl     0x457270
  457295:	e9 56 00 00 00       	jmp    0x4572f0
  45729a:	8b 8b b4 ed 6e 00    	mov    ecx,DWORD PTR [ebx+0x6eedb4]
  4572a0:	8d 46 05             	lea    eax,[esi+0x5]
  4572a3:	57                   	push   edi
  4572a4:	50                   	push   eax
  4572a5:	33 d2                	xor    edx,edx
  4572a7:	e8 d4 4a 0a 00       	call   0x4fbd80

Caller 004fc160, CALL 004fc1b9, last 35 disassembly lines from function entry:

/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe:     file format pei-i386


Disassembly of section .text:

004fc160 <.text+0xfb160>:
  4fc160:	55                   	push   ebp
  4fc161:	8b ec                	mov    ebp,esp
  4fc163:	81 ec 08 04 00 00    	sub    esp,0x408
  4fc169:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  4fc16e:	33 c5                	xor    eax,ebp
  4fc170:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  4fc173:	0f 10 05 54 a7 5a 00 	movups xmm0,XMMWORD PTR ds:0x5aa754
  4fc17a:	a1 6c a7 5a 00       	mov    eax,ds:0x5aa76c
  4fc17f:	8b ca                	mov    ecx,edx
  4fc181:	89 85 10 fc ff ff    	mov    DWORD PTR [ebp-0x3f0],eax
  4fc187:	8d 95 f8 fb ff ff    	lea    edx,[ebp-0x408]
  4fc18d:	a0 70 a7 5a 00       	mov    al,ds:0x5aa770
  4fc192:	0f 11 85 f8 fb ff ff 	movups XMMWORD PTR [ebp-0x408],xmm0
  4fc199:	68 1f 02 00 00       	push   0x21f
  4fc19e:	f3 0f 7e 05 64 a7 5a 	movq   xmm0,QWORD PTR ds:0x5aa764
  4fc1a5:	00 
  4fc1a6:	68 f4 01 00 00       	push   0x1f4
  4fc1ab:	66 0f d6 85 08 fc ff 	movq   QWORD PTR [ebp-0x3f8],xmm0
  4fc1b2:	ff 
  4fc1b3:	88 85 14 fc ff ff    	mov    BYTE PTR [ebp-0x3ec],al
  4fc1b9:	e8 c2 fb ff ff       	call   0x4fbd80

Caller 00438240, CALL 004383ed, last 35 disassembly lines from function entry:
  438376:	e8 85 7c 00 00       	call   0x440000
  43837b:	8d 55 90             	lea    edx,[ebp-0x70]
  43837e:	2b d0                	sub    edx,eax
  438380:	8a 08                	mov    cl,BYTE PTR [eax]
  438382:	8d 40 01             	lea    eax,[eax+0x1]
  438385:	88 4c 02 ff          	mov    BYTE PTR [edx+eax*1-0x1],cl
  438389:	84 c9                	test   cl,cl
  43838b:	75 f3                	jne    0x438380
  43838d:	8d 85 00 85 ff ff    	lea    eax,[ebp-0x7b00]
  438393:	8b cb                	mov    ecx,ebx
  438395:	50                   	push   eax
  438396:	8d 55 90             	lea    edx,[ebp-0x70]
  438399:	e8 62 78 00 00       	call   0x43fc00
  43839e:	8b 1d 50 c3 58 00    	mov    ebx,DWORD PTR ds:0x58c350
  4383a4:	8d 85 28 fb ff ff    	lea    eax,[ebp-0x4d8]
  4383aa:	83 c4 04             	add    esp,0x4
  4383ad:	be 01 00 00 00       	mov    esi,0x1
  4383b2:	89 b5 f8 84 ff ff    	mov    DWORD PTR [ebp-0x7b08],esi
  4383b8:	68 0c 3e 59 00       	push   0x593e0c
  4383bd:	50                   	push   eax
  4383be:	ff d3                	call   ebx
  4383c0:	8b 3d 74 c3 58 00    	mov    edi,DWORD PTR ds:0x58c374
  4383c6:	83 c4 08             	add    esp,0x8
  4383c9:	85 c0                	test   eax,eax
  4383cb:	74 3f                	je     0x43840c
  4383cd:	68 18 3e 59 00       	push   0x593e18
  4383d2:	ba 1c 3e 59 00       	mov    edx,0x593e1c
  4383d7:	8d 8d 28 fb ff ff    	lea    ecx,[ebp-0x4d8]
  4383dd:	e8 1e 78 12 00       	call   0x55fc00
  4383e2:	83 c4 04             	add    esp,0x4
  4383e5:	50                   	push   eax
  4383e6:	ff d7                	call   edi
  4383e8:	83 c4 04             	add    esp,0x4
  4383eb:	8b d0                	mov    edx,eax
  4383ed:	e8 6e 3d 0c 00       	call   0x4fc160

Caller 00468ac0, CALL 00469485, last 35 disassembly lines from function entry:
  4693ec:	83 c4 0c             	add    esp,0xc
  4693ef:	83 3d a0 28 6d 0a 00 	cmp    DWORD PTR ds:0xa6d28a0,0x0
  4693f6:	0f b6 05 f2 f4 18 05 	movzx  eax,BYTE PTR ds:0x518f4f2
  4693fd:	89 44 24 40          	mov    DWORD PTR [esp+0x40],eax
  469401:	74 34                	je     0x469437
  469403:	8d 84 24 f8 0e 00 00 	lea    eax,[esp+0xef8]
  46940a:	c6 05 f2 f4 18 05 00 	mov    BYTE PTR ds:0x518f4f2,0x0
  469411:	50                   	push   eax
  469412:	68 9c ad 5a 00       	push   0x5aad9c
  469417:	68 88 92 5a 06       	push   0x65a9288
  46941c:	e8 af 7c f9 ff       	call   0x4010d0
  469421:	83 c4 0c             	add    esp,0xc
  469424:	b9 88 92 5a 06       	mov    ecx,0x65a9288
  469429:	e8 e2 d0 08 00       	call   0x4f6510
  46942e:	8b 44 24 40          	mov    eax,DWORD PTR [esp+0x40]
  469432:	a2 f2 f4 18 05       	mov    ds:0x518f4f2,al
  469437:	83 fb ff             	cmp    ebx,0xffffffff
  46943a:	0f 84 23 ff ff ff    	je     0x469363
  469440:	8b 4c 24 4c          	mov    ecx,DWORD PTR [esp+0x4c]
  469444:	0f 57 c9             	xorps  xmm1,xmm1
  469447:	8b 94 24 84 00 00 00 	mov    edx,DWORD PTR [esp+0x84]
  46944e:	f3 0f 10 81 f0 01 00 	movss  xmm0,DWORD PTR [ecx+0x1f0]
  469455:	00 
  469456:	0f 2e c1             	ucomiss xmm0,xmm1
  469459:	9f                   	lahf
  46945a:	f6 c4 44             	test   ah,0x44
  46945d:	0f 8a 8e 00 00 00    	jp     0x4694f1
  469463:	85 d2                	test   edx,edx
  469465:	0f 85 86 00 00 00    	jne    0x4694f1
  46946b:	39 91 f8 01 00 00    	cmp    DWORD PTR [ecx+0x1f8],edx
  469471:	0f 85 7a 00 00 00    	jne    0x4694f1
  469477:	8b 14 9d 60 ae 72 0a 	mov    edx,DWORD PTR [ebx*4+0xa72ae60]
  46947e:	33 c9                	xor    ecx,ecx
  469480:	c6 44 24 66 01       	mov    BYTE PTR [esp+0x66],0x1
  469485:	e8 46 2d 09 00       	call   0x4fc1d0

Caller 00520180, CALL 00520606, last 35 disassembly lines from function entry:
  520574:	68 00 e8 5a 00       	push   0x5ae800
  520579:	50                   	push   eax
  52057a:	e8 51 0b ee ff       	call   0x4010d0
  52057f:	83 c4 0c             	add    esp,0xc
  520582:	8d 8c 24 b8 18 00 00 	lea    ecx,[esp+0x18b8]
  520589:	e8 82 5f fd ff       	call   0x4f6510
  52058e:	68 54 16 00 00       	push   0x1654
  520593:	8d 84 24 64 02 00 00 	lea    eax,[esp+0x264]
  52059a:	68 e8 a6 72 0a       	push   0xa72a6e8
  52059f:	50                   	push   eax
  5205a0:	e8 fb af 06 00       	call   0x58b5a0
  5205a5:	83 c4 0c             	add    esp,0xc
  5205a8:	83 3d f4 0a 6d 0a 01 	cmp    DWORD PTR ds:0xa6d0af4,0x1
  5205af:	0f 85 a1 00 00 00    	jne    0x520656
  5205b5:	b9 48 e8 5a 00       	mov    ecx,0x5ae848
  5205ba:	e8 51 5f fd ff       	call   0x4f6510
  5205bf:	83 3d f4 0a 6d 0a 01 	cmp    DWORD PTR ds:0xa6d0af4,0x1
  5205c6:	66 0f 6e c7          	movd   xmm0,edi
  5205ca:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  5205cd:	75 08                	jne    0x5205d7
  5205cf:	f3 0f 5e 05 98 d4 5d 	divss  xmm0,DWORD PTR ds:0x5dd498
  5205d6:	00 
  5205d7:	0f 5a c0             	cvtps2pd xmm0,xmm0
  5205da:	83 ec 08             	sub    esp,0x8
  5205dd:	f2 0f 11 44 24 28    	movsd  QWORD PTR [esp+0x28],xmm0
  5205e3:	dd 44 24 28          	fld    QWORD PTR [esp+0x28]
  5205e7:	dd 1c 24             	fstp   QWORD PTR [esp]
  5205ea:	e8 ed af 06 00       	call   0x58b5dc
  5205ef:	dd 5c 24 28          	fstp   QWORD PTR [esp+0x28]
  5205f3:	f2 0f 10 44 24 28    	movsd  xmm0,QWORD PTR [esp+0x28]
  5205f9:	83 c4 08             	add    esp,0x8
  5205fc:	66 0f 5a c0          	cvtpd2ps xmm0,xmm0
  520600:	33 c9                	xor    ecx,ecx
  520602:	f3 0f 2c d0          	cvttss2si edx,xmm0
  520606:	e8 c5 bb fd ff       	call   0x4fc1d0

Caller 00520180, CALL 00520667, last 35 disassembly lines from function entry:
  5205fc:	66 0f 5a c0          	cvtpd2ps xmm0,xmm0
  520600:	33 c9                	xor    ecx,ecx
  520602:	f3 0f 2c d0          	cvttss2si edx,xmm0
  520606:	e8 c5 bb fd ff       	call   0x4fc1d0
  52060b:	8b c8                	mov    ecx,eax
  52060d:	85 c9                	test   ecx,ecx
  52060f:	75 1f                	jne    0x520630
  520611:	b9 f0 5e 59 00       	mov    ecx,0x595ef0
  520616:	e8 f5 5e fd ff       	call   0x4f6510
  52061b:	5f                   	pop    edi
  52061c:	5e                   	pop    esi
  52061d:	5b                   	pop    ebx
  52061e:	8b 8c 24 b0 1c 00 00 	mov    ecx,DWORD PTR [esp+0x1cb0]
  520625:	33 cc                	xor    ecx,esp
  520627:	e8 82 9a 06 00       	call   0x58a0ae
  52062c:	8b e5                	mov    esp,ebp
  52062e:	5d                   	pop    ebp
  52062f:	c3                   	ret
  520630:	8d 04 49             	lea    eax,[ecx+ecx*2]
  520633:	66 0f 6e c9          	movd   xmm1,ecx
  520637:	89 44 24 1c          	mov    DWORD PTR [esp+0x1c],eax
  52063b:	8d 44 24 48          	lea    eax,[esp+0x48]
  52063f:	50                   	push   eax
  520640:	b8 56 55 55 55       	mov    eax,0x55555556
  520645:	f7 6c 24 1c          	imul   DWORD PTR [esp+0x1c]
  520649:	8b c2                	mov    eax,edx
  52064b:	c1 e8 1f             	shr    eax,0x1f
  52064e:	03 c2                	add    eax,edx
  520650:	66 0f 6e c0          	movd   xmm0,eax
  520654:	eb 2d                	jmp    0x520683
  520656:	b9 74 e8 5a 00       	mov    ecx,0x5ae874
  52065b:	e8 b0 5e fd ff       	call   0x4f6510
  520660:	8b d7                	mov    edx,edi
  520662:	b9 03 00 00 00       	mov    ecx,0x3
  520667:	e8 64 bb fd ff       	call   0x4fc1d0

Caller 00404030, CALL 00404162, last 35 disassembly lines from function entry:
  4040d4:	8b 9b ac ed 6e 00    	mov    ebx,DWORD PTR [ebx+0x6eedac]
  4040da:	85 db                	test   ebx,ebx
  4040dc:	79 1d                	jns    0x4040fb
  4040de:	81 fb 48 f4 ff ff    	cmp    ebx,0xfffff448
  4040e4:	0f 85 86 05 00 00    	jne    0x404670
  4040ea:	b9 c8 cb 58 00       	mov    ecx,0x58cbc8
  4040ef:	e8 4c ec 15 00       	call   0x562d40
  4040f4:	8b c8                	mov    ecx,eax
  4040f6:	e9 70 05 00 00       	jmp    0x40466b
  4040fb:	8b 0c 9d d0 ac 72 0a 	mov    ecx,DWORD PTR [ebx*4+0xa72acd0]
  404102:	8d 84 24 b0 01 00 00 	lea    eax,[esp+0x1b0]
  404109:	50                   	push   eax
  40410a:	e8 81 c0 0b 00       	call   0x4c0190
  40410f:	8b f0                	mov    esi,eax
  404111:	8d 7c 24 54          	lea    edi,[esp+0x54]
  404115:	b9 2b 00 00 00       	mov    ecx,0x2b
  40411a:	81 ec a8 00 00 00    	sub    esp,0xa8
  404120:	f3 a5                	rep movs DWORD PTR es:[edi],DWORD PTR ds:[esi]
  404122:	8b f0                	mov    esi,eax
  404124:	b9 2b 00 00 00       	mov    ecx,0x2b
  404129:	8b fc                	mov    edi,esp
  40412b:	f3 a5                	rep movs DWORD PTR es:[edi],DWORD PTR ds:[esi]
  40412d:	e8 fe 06 03 00       	call   0x434830
  404132:	81 c4 ac 00 00 00    	add    esp,0xac
  404138:	84 c0                	test   al,al
  40413a:	75 1d                	jne    0x404159
  40413c:	8b 04 9d d0 ac 72 0a 	mov    eax,DWORD PTR [ebx*4+0xa72acd0]
  404143:	b9 f8 cb 58 00       	mov    ecx,0x58cbf8
  404148:	a3 4c 28 62 0a       	mov    ds:0xa62284c,eax
  40414d:	e8 ae d9 15 00       	call   0x561b00
  404152:	8b c8                	mov    ecx,eax
  404154:	e9 12 05 00 00       	jmp    0x40466b
  404159:	8b 14 9d 60 ae 72 0a 	mov    edx,DWORD PTR [ebx*4+0xa72ae60]
  404160:	33 c9                	xor    ecx,ecx
  404162:	e8 69 80 0f 00       	call   0x4fc1d0

Caller 00447180, CALL 004473a4, last 35 disassembly lines from function entry:
  44731f:	51                   	push   ecx
  447320:	33 c9                	xor    ecx,ecx
  447322:	e8 d9 44 00 00       	call   0x44b800
  447327:	83 c4 04             	add    esp,0x4
  44732a:	50                   	push   eax
  44732b:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  447331:	68 50 72 59 00       	push   0x597250
  447336:	50                   	push   eax
  447337:	e8 94 9d fb ff       	call   0x4010d0
  44733c:	83 c4 10             	add    esp,0x10
  44733f:	8d 8d f8 fb ff ff    	lea    ecx,[ebp-0x408]
  447345:	e8 c6 f1 0a 00       	call   0x4f6510
  44734a:	83 3d f4 0a 6d 0a 01 	cmp    DWORD PTR ds:0xa6d0af4,0x1
  447351:	75 63                	jne    0x4473b6
  447353:	f3 0f 10 85 f4 fb ff 	movss  xmm0,DWORD PTR [ebp-0x40c]
  44735a:	ff 
  44735b:	8d 85 e0 fb ff ff    	lea    eax,[ebp-0x420]
  447361:	0f 5a c0             	cvtps2pd xmm0,xmm0
  447364:	50                   	push   eax
  447365:	83 ec 08             	sub    esp,0x8
  447368:	f2 0f 11 04 24       	movsd  QWORD PTR [esp],xmm0
  44736d:	ff 15 f0 c3 58 00    	call   DWORD PTR ds:0x58c3f0
  447373:	f2 0f 2c 95 e0 fb ff 	cvttsd2si edx,QWORD PTR [ebp-0x420]
  44737a:	ff 
  44737b:	83 c4 0c             	add    esp,0xc
  44737e:	33 c9                	xor    ecx,ecx
  447380:	d9 9d f4 fb ff ff    	fstp   DWORD PTR [ebp-0x40c]
  447386:	d9 85 f4 fb ff ff    	fld    DWORD PTR [ebp-0x40c]
  44738c:	d9 9d f4 fb ff ff    	fstp   DWORD PTR [ebp-0x40c]
  447392:	f3 0f 10 85 f4 fb ff 	movss  xmm0,DWORD PTR [ebp-0x40c]
  447399:	ff 
  44739a:	0f 2f 05 70 d0 5d 00 	comiss xmm0,DWORD PTR ds:0x5dd070
  4473a1:	77 01                	ja     0x4473a4
  4473a3:	4a                   	dec    edx
  4473a4:	e8 27 4e 0b 00       	call   0x4fc1d0

Caller 00447180, CALL 004473bb, last 35 disassembly lines from function entry:
  447336:	50                   	push   eax
  447337:	e8 94 9d fb ff       	call   0x4010d0
  44733c:	83 c4 10             	add    esp,0x10
  44733f:	8d 8d f8 fb ff ff    	lea    ecx,[ebp-0x408]
  447345:	e8 c6 f1 0a 00       	call   0x4f6510
  44734a:	83 3d f4 0a 6d 0a 01 	cmp    DWORD PTR ds:0xa6d0af4,0x1
  447351:	75 63                	jne    0x4473b6
  447353:	f3 0f 10 85 f4 fb ff 	movss  xmm0,DWORD PTR [ebp-0x40c]
  44735a:	ff 
  44735b:	8d 85 e0 fb ff ff    	lea    eax,[ebp-0x420]
  447361:	0f 5a c0             	cvtps2pd xmm0,xmm0
  447364:	50                   	push   eax
  447365:	83 ec 08             	sub    esp,0x8
  447368:	f2 0f 11 04 24       	movsd  QWORD PTR [esp],xmm0
  44736d:	ff 15 f0 c3 58 00    	call   DWORD PTR ds:0x58c3f0
  447373:	f2 0f 2c 95 e0 fb ff 	cvttsd2si edx,QWORD PTR [ebp-0x420]
  44737a:	ff 
  44737b:	83 c4 0c             	add    esp,0xc
  44737e:	33 c9                	xor    ecx,ecx
  447380:	d9 9d f4 fb ff ff    	fstp   DWORD PTR [ebp-0x40c]
  447386:	d9 85 f4 fb ff ff    	fld    DWORD PTR [ebp-0x40c]
  44738c:	d9 9d f4 fb ff ff    	fstp   DWORD PTR [ebp-0x40c]
  447392:	f3 0f 10 85 f4 fb ff 	movss  xmm0,DWORD PTR [ebp-0x40c]
  447399:	ff 
  44739a:	0f 2f 05 70 d0 5d 00 	comiss xmm0,DWORD PTR ds:0x5dd070
  4473a1:	77 01                	ja     0x4473a4
  4473a3:	4a                   	dec    edx
  4473a4:	e8 27 4e 0b 00       	call   0x4fc1d0
  4473a9:	85 c0                	test   eax,eax
  4473ab:	0f 84 60 02 00 00    	je     0x447611
  4473b1:	8d 04 40             	lea    eax,[eax+eax*2]
  4473b4:	eb 0a                	jmp    0x4473c0
  4473b6:	8d 56 ff             	lea    edx,[esi-0x1]
  4473b9:	33 c9                	xor    ecx,ecx
  4473bb:	e8 10 4e 0b 00       	call   0x4fc1d0

Caller 00438240, CALL 00438446, last 35 disassembly lines from function entry:
  4383cb:	74 3f                	je     0x43840c
  4383cd:	68 18 3e 59 00       	push   0x593e18
  4383d2:	ba 1c 3e 59 00       	mov    edx,0x593e1c
  4383d7:	8d 8d 28 fb ff ff    	lea    ecx,[ebp-0x4d8]
  4383dd:	e8 1e 78 12 00       	call   0x55fc00
  4383e2:	83 c4 04             	add    esp,0x4
  4383e5:	50                   	push   eax
  4383e6:	ff d7                	call   edi
  4383e8:	83 c4 04             	add    esp,0x4
  4383eb:	8b d0                	mov    edx,eax
  4383ed:	e8 6e 3d 0c 00       	call   0x4fc160
  4383f2:	8b f0                	mov    esi,eax
  4383f4:	85 f6                	test   esi,esi
  4383f6:	0f 84 e4 04 00 00    	je     0x4388e0
  4383fc:	c7 85 f8 84 ff ff 01 	mov    DWORD PTR [ebp-0x7b08],0x1
  438403:	00 00 00 
  438406:	89 b5 fc 84 ff ff    	mov    DWORD PTR [ebp-0x7b04],esi
  43840c:	8d 85 28 fb ff ff    	lea    eax,[ebp-0x4d8]
  438412:	68 24 3e 59 00       	push   0x593e24
  438417:	50                   	push   eax
  438418:	ff d3                	call   ebx
  43841a:	83 c4 08             	add    esp,0x8
  43841d:	85 c0                	test   eax,eax
  43841f:	74 3e                	je     0x43845f
  438421:	68 18 3e 59 00       	push   0x593e18
  438426:	ba 2c 3e 59 00       	mov    edx,0x593e2c
  43842b:	8d 8d 28 fb ff ff    	lea    ecx,[ebp-0x4d8]
  438431:	e8 ca 77 12 00       	call   0x55fc00
  438436:	83 c4 04             	add    esp,0x4
  438439:	50                   	push   eax
  43843a:	ff d7                	call   edi
  43843c:	83 c4 04             	add    esp,0x4
  43843f:	8b d0                	mov    edx,eax
  438441:	b9 01 00 00 00       	mov    ecx,0x1
  438446:	e8 85 3d 0c 00       	call   0x4fc1d0

Caller 004416a0, CALL 00441df5, last 35 disassembly lines from function entry:
  441d78:	85 f6                	test   esi,esi
  441d7a:	74 42                	je     0x441dbe
  441d7c:	bb 01 00 00 00       	mov    ebx,0x1
  441d81:	be 20 0d 13 02       	mov    esi,0x2130d20
  441d86:	80 7e 2f 00          	cmp    BYTE PTR [esi+0x2f],0x0
  441d8a:	0f 84 3e 01 00 00    	je     0x441ece
  441d90:	8b 46 dc             	mov    eax,DWORD PTR [esi-0x24]
  441d93:	83 f8 01             	cmp    eax,0x1
  441d96:	0f 87 b2 00 00 00    	ja     0x441e4e
  441d9c:	8b 0e                	mov    ecx,DWORD PTR [esi]
  441d9e:	85 c9                	test   ecx,ecx
  441da0:	0f 84 a8 00 00 00    	je     0x441e4e
  441da6:	83 7e 04 00          	cmp    DWORD PTR [esi+0x4],0x0
  441daa:	0f 84 97 00 00 00    	je     0x441e47
  441db0:	89 5e 04             	mov    DWORD PTR [esi+0x4],ebx
  441db3:	e9 9c 00 00 00       	jmp    0x441e54
  441db8:	8b 3d 50 c3 58 00    	mov    edi,DWORD PTR ds:0x58c350
  441dbe:	8d 85 a8 f9 ff ff    	lea    eax,[ebp-0x658]
  441dc4:	68 24 3e 59 00       	push   0x593e24
  441dc9:	50                   	push   eax
  441dca:	ff d7                	call   edi
  441dcc:	83 c4 08             	add    esp,0x8
  441dcf:	85 c0                	test   eax,eax
  441dd1:	74 50                	je     0x441e23
  441dd3:	68 18 3e 59 00       	push   0x593e18
  441dd8:	ba 2c 3e 59 00       	mov    edx,0x593e2c
  441ddd:	8d 8d a8 f9 ff ff    	lea    ecx,[ebp-0x658]
  441de3:	e8 18 de 11 00       	call   0x55fc00
  441de8:	83 c4 04             	add    esp,0x4
  441deb:	50                   	push   eax
  441dec:	ff d3                	call   ebx
  441dee:	83 c4 04             	add    esp,0x4
  441df1:	8b d0                	mov    edx,eax
  441df3:	33 c9                	xor    ecx,ecx
  441df5:	e8 d6 a3 0b 00       	call   0x4fc1d0
