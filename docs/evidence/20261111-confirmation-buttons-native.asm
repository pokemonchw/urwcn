; Original PE VA 0x4cfaf0..0x4cfcfc
  4cfaf0:	55                   	push   ebp
  4cfaf1:	8b ec                	mov    ebp,esp
  4cfaf3:	81 ec 14 04 00 00    	sub    esp,0x414
  4cfaf9:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  4cfafe:	33 c5                	xor    eax,ebp
  4cfb00:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  4cfb03:	8b 45 0c             	mov    eax,DWORD PTR [ebp+0xc]
  4cfb06:	53                   	push   ebx
  4cfb07:	56                   	push   esi
  4cfb08:	57                   	push   edi
  4cfb09:	8b 3d 34 4a 35 06    	mov    edi,DWORD PTR ds:0x6354a34
  4cfb0f:	33 f6                	xor    esi,esi
  4cfb11:	89 95 f4 fb ff ff    	mov    DWORD PTR [ebp-0x40c],edx
  4cfb17:	8b d9                	mov    ebx,ecx
  4cfb19:	89 85 f0 fb ff ff    	mov    DWORD PTR [ebp-0x410],eax
  4cfb1f:	85 ff                	test   edi,edi
  4cfb21:	7e 35                	jle    0x4cfb58
  4cfb23:	8b 0d b0 49 35 06    	mov    ecx,DWORD PTR ds:0x63549b0
  4cfb29:	b8 d8 ef 34 06       	mov    eax,0x634efd8
  4cfb2e:	66 90                	xchg   ax,ax
  4cfb30:	39 18                	cmp    DWORD PTR [eax],ebx
  4cfb32:	75 14                	jne    0x4cfb48
  4cfb34:	be 01 00 00 00       	mov    esi,0x1
  4cfb39:	85 c9                	test   ecx,ecx
  4cfb3b:	74 0b                	je     0x4cfb48
  4cfb3d:	33 d2                	xor    edx,edx
  4cfb3f:	81 fb 23 04 00 00    	cmp    ebx,0x423
  4cfb45:	0f 45 f2             	cmovne esi,edx
  4cfb48:	05 e8 00 00 00       	add    eax,0xe8
  4cfb4d:	83 ef 01             	sub    edi,0x1
  4cfb50:	75 de                	jne    0x4cfb30
  4cfb52:	8b 85 f0 fb ff ff    	mov    eax,DWORD PTR [ebp-0x410]
  4cfb58:	8d 95 f8 fb ff ff    	lea    edx,[ebp-0x408]
  4cfb5e:	8b c8                	mov    ecx,eax
  4cfb60:	2b d0                	sub    edx,eax
  4cfb62:	8a 01                	mov    al,BYTE PTR [ecx]
  4cfb64:	8d 49 01             	lea    ecx,[ecx+0x1]
  4cfb67:	88 44 0a ff          	mov    BYTE PTR [edx+ecx*1-0x1],al
  4cfb6b:	84 c0                	test   al,al
  4cfb6d:	75 f3                	jne    0x4cfb62
  4cfb6f:	a1 30 4a 35 06       	mov    eax,ds:0x6354a30
  4cfb74:	8b 7d 08             	mov    edi,DWORD PTR [ebp+0x8]
  4cfb77:	8b d7                	mov    edx,edi
  4cfb79:	8b 8d f4 fb ff ff    	mov    ecx,DWORD PTR [ebp-0x40c]
  4cfb7f:	a3 c4 ba 5b 06       	mov    ds:0x65bbac4,eax
  4cfb84:	a1 9c 4a 35 06       	mov    eax,ds:0x6354a9c
  4cfb89:	a3 54 ba 5b 06       	mov    ds:0x65bba54,eax
  4cfb8e:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  4cfb94:	50                   	push   eax
  4cfb95:	e8 e6 4a 04 00       	call   0x514680
  4cfb9a:	83 c4 04             	add    esp,0x4
  4cfb9d:	c7 05 54 ba 5b 06 00 	mov    DWORD PTR ds:0x65bba54,0x0
  4cfba4:	00 00 00 
  4cfba7:	c7 05 c4 ba 5b 06 00 	mov    DWORD PTR ds:0x65bbac4,0x0
  4cfbae:	00 00 00 
  4cfbb1:	85 f6                	test   esi,esi
  4cfbb3:	0f 85 32 01 00 00    	jne    0x4cfceb
  4cfbb9:	69 0d 34 4a 35 06 e8 	imul   ecx,DWORD PTR ds:0x6354a34,0xe8
  4cfbc0:	00 00 00 
  4cfbc3:	8b 85 f4 fb ff ff    	mov    eax,DWORD PTR [ebp-0x40c]
  4cfbc9:	8b 35 48 c3 58 00    	mov    esi,DWORD PTR ds:0x58c348
  4cfbcf:	83 c0 02             	add    eax,0x2
  4cfbd2:	6a 2e                	push   0x2e
  4cfbd4:	89 99 d8 ef 34 06    	mov    DWORD PTR [ecx+0x634efd8],ebx
  4cfbda:	89 81 e0 ef 34 06    	mov    DWORD PTR [ecx+0x634efe0],eax
  4cfbe0:	8d 47 01             	lea    eax,[edi+0x1]
  4cfbe3:	89 81 e4 ef 34 06    	mov    DWORD PTR [ecx+0x634efe4],eax
  4cfbe9:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  4cfbef:	50                   	push   eax
  4cfbf0:	c7 81 ec ef 34 06 12 	mov    DWORD PTR [ecx+0x634efec],0x12
  4cfbf7:	00 00 00 
  4cfbfa:	ff d6                	call   esi
  4cfbfc:	83 c4 08             	add    esp,0x8
  4cfbff:	85 c0                	test   eax,eax
  4cfc01:	74 1b                	je     0x4cfc1e
  4cfc03:	8d 8d f8 fb ff ff    	lea    ecx,[ebp-0x408]
  4cfc09:	2b c1                	sub    eax,ecx
  4cfc0b:	3d 00 04 00 00       	cmp    eax,0x400
  4cfc10:	0f 83 e6 00 00 00    	jae    0x4cfcfc
  4cfc16:	c6 84 05 f8 fb ff ff 	mov    BYTE PTR [ebp+eax*1-0x408],0x0
  4cfc1d:	00 
  4cfc1e:	8d 8d f8 fb ff ff    	lea    ecx,[ebp-0x408]
  4cfc24:	8d 51 01             	lea    edx,[ecx+0x1]
  4cfc27:	8a 01                	mov    al,BYTE PTR [ecx]
  4cfc29:	41                   	inc    ecx
  4cfc2a:	84 c0                	test   al,al
  4cfc2c:	75 f9                	jne    0x4cfc27
  4cfc2e:	8b bd f0 fb ff ff    	mov    edi,DWORD PTR [ebp-0x410]
  4cfc34:	2b ca                	sub    ecx,edx
  4cfc36:	69 15 34 4a 35 06 e8 	imul   edx,DWORD PTR ds:0x6354a34,0xe8
  4cfc3d:	00 00 00 
  4cfc40:	8d 04 cd 0a 00 00 00 	lea    eax,[ecx*8+0xa]
  4cfc47:	8b cf                	mov    ecx,edi
  4cfc49:	8d 59 01             	lea    ebx,[ecx+0x1]
  4cfc4c:	89 82 f4 ef 34 06    	mov    DWORD PTR [edx+0x634eff4],eax
  4cfc52:	8a 01                	mov    al,BYTE PTR [ecx]
  4cfc54:	41                   	inc    ecx
  4cfc55:	84 c0                	test   al,al
  4cfc57:	75 f9                	jne    0x4cfc52
  4cfc59:	2b cb                	sub    ecx,ebx
  4cfc5b:	6a 3c                	push   0x3c
  4cfc5d:	8d 04 cd 0a 00 00 00 	lea    eax,[ecx*8+0xa]
  4cfc64:	89 82 e8 ef 34 06    	mov    DWORD PTR [edx+0x634efe8],eax
  4cfc6a:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  4cfc70:	50                   	push   eax
  4cfc71:	ff d6                	call   esi
  4cfc73:	83 c4 08             	add    esp,0x8
  4cfc76:	85 c0                	test   eax,eax
  4cfc78:	74 18                	je     0x4cfc92
  4cfc7a:	69 05 34 4a 35 06 e8 	imul   eax,DWORD PTR ds:0x6354a34,0xe8
  4cfc81:	00 00 00 
  4cfc84:	83 80 e8 ef 34 06 f0 	add    DWORD PTR [eax+0x634efe8],0xfffffff0
  4cfc8b:	83 80 f4 ef 34 06 f0 	add    DWORD PTR [eax+0x634eff4],0xfffffff0
  4cfc92:	6a 2e                	push   0x2e
  4cfc94:	57                   	push   edi
  4cfc95:	ff d6                	call   esi
  4cfc97:	8b 15 34 4a 35 06    	mov    edx,DWORD PTR ds:0x6354a34
  4cfc9d:	83 c4 08             	add    esp,0x8
  4cfca0:	69 ca e8 00 00 00    	imul   ecx,edx,0xe8
  4cfca6:	81 c1 10 ef 34 06    	add    ecx,0x634ef10
  4cfcac:	85 c0                	test   eax,eax
  4cfcae:	75 20                	jne    0x4cfcd0
  4cfcb0:	f3 0f 7e 05 f4 4d 5a 	movq   xmm0,QWORD PTR ds:0x5a4df4
  4cfcb7:	00 
  4cfcb8:	66 a1 fc 4d 5a 00    	mov    ax,ds:0x5a4dfc
  4cfcbe:	66 0f d6 01          	movq   QWORD PTR [ecx],xmm0
  4cfcc2:	66 89 41 08          	mov    WORD PTR [ecx+0x8],ax
  4cfcc6:	a0 fe 4d 5a 00       	mov    al,ds:0x5a4dfe
  4cfccb:	88 41 0a             	mov    BYTE PTR [ecx+0xa],al
  4cfcce:	eb 14                	jmp    0x4cfce4
  4cfcd0:	f3 0f 7e 05 00 4e 5a 	movq   xmm0,QWORD PTR ds:0x5a4e00
  4cfcd7:	00 
  4cfcd8:	a0 08 4e 5a 00       	mov    al,ds:0x5a4e08
  4cfcdd:	66 0f d6 01          	movq   QWORD PTR [ecx],xmm0
  4cfce1:	88 41 08             	mov    BYTE PTR [ecx+0x8],al
  4cfce4:	42                   	inc    edx
  4cfce5:	89 15 34 4a 35 06    	mov    DWORD PTR ds:0x6354a34,edx
  4cfceb:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  4cfcee:	5f                   	pop    edi
  4cfcef:	5e                   	pop    esi
  4cfcf0:	33 cd                	xor    ecx,ebp
  4cfcf2:	5b                   	pop    ebx
  4cfcf3:	e8 b6 a3 0b 00       	call   0x58a0ae
  4cfcf8:	8b e5                	mov    esp,ebp
  4cfcfa:	5d                   	pop    ebp
  4cfcfb:	c3                   	ret

; Original PE VA 0x4cffb0..0x4d00e4
  4cffb0:	55                   	push   ebp
  4cffb1:	8b ec                	mov    ebp,esp
  4cffb3:	83 ec 0c             	sub    esp,0xc
  4cffb6:	a1 28 4a 35 06       	mov    eax,ds:0x6354a28
  4cffbb:	53                   	push   ebx
  4cffbc:	56                   	push   esi
  4cffbd:	8b 35 20 4a 35 06    	mov    esi,DWORD PTR ds:0x6354a20
  4cffc3:	48                   	dec    eax
  4cffc4:	57                   	push   edi
  4cffc5:	8b 3d 24 4a 35 06    	mov    edi,DWORD PTR ds:0x6354a24
  4cffcb:	03 f0                	add    esi,eax
  4cffcd:	a1 2c 4a 35 06       	mov    eax,ds:0x6354a2c
  4cffd2:	48                   	dec    eax
  4cffd3:	6a 54                	push   0x54
  4cffd5:	03 f8                	add    edi,eax
  4cffd7:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4cffdc:	68 fc 00 00 00       	push   0xfc
  4cffe1:	68 fc 00 00 00       	push   0xfc
  4cffe6:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4cffe9:	ff 15 f8 c1 58 00    	call   DWORD PTR ds:0x58c1f8
  4cffef:	83 c4 10             	add    esp,0x10
  4cfff2:	8b d8                	mov    ebx,eax
  4cfff4:	83 3d a4 4a 35 06 64 	cmp    DWORD PTR ds:0x6354aa4,0x64
  4cfffb:	a1 24 4a 35 06       	mov    eax,ds:0x6354a24
  4d0000:	89 45 f4             	mov    DWORD PTR [ebp-0xc],eax
  4d0003:	0f 85 db 00 00 00    	jne    0x4d00e4
  4d0009:	68 0c 4e 5a 00       	push   0x5a4e0c
  4d000e:	68 38 4a 35 06       	push   0x6354a38
  4d0013:	ff 15 50 c3 58 00    	call   DWORD PTR ds:0x58c350
  4d0019:	83 c4 08             	add    esp,0x8
  4d001c:	85 c0                	test   eax,eax
  4d001e:	0f 84 d9 03 00 00    	je     0x4d03fd
  4d0024:	83 3d 34 4a 35 06 00 	cmp    DWORD PTR ds:0x6354a34,0x0
  4d002b:	c7 45 f8 00 00 00 00 	mov    DWORD PTR [ebp-0x8],0x0
  4d0032:	0f 8e c5 03 00 00    	jle    0x4d03fd
  4d0038:	bf e4 ef 34 06       	mov    edi,0x634efe4
  4d003d:	89 7d f4             	mov    DWORD PTR [ebp-0xc],edi
  4d0040:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4d0045:	6a 54                	push   0x54
  4d0047:	68 fc 00 00 00       	push   0xfc
  4d004c:	68 fc 00 00 00       	push   0xfc
  4d0051:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4d0054:	ff 15 f8 c1 58 00    	call   DWORD PTR ds:0x58c1f8
  4d005a:	8b 17                	mov    edx,DWORD PTR [edi]
  4d005c:	8b 5f 08             	mov    ebx,DWORD PTR [edi+0x8]
  4d005f:	8b 77 fc             	mov    esi,DWORD PTR [edi-0x4]
  4d0062:	4b                   	dec    ebx
  4d0063:	8b 7f 04             	mov    edi,DWORD PTR [edi+0x4]
  4d0066:	8b ce                	mov    ecx,esi
  4d0068:	50                   	push   eax
  4d0069:	4f                   	dec    edi
  4d006a:	a3 68 10 61 0a       	mov    ds:0xa611068,eax
  4d006f:	52                   	push   edx
  4d0070:	03 fe                	add    edi,esi
  4d0072:	89 55 fc             	mov    DWORD PTR [ebp-0x4],edx
  4d0075:	57                   	push   edi
  4d0076:	03 da                	add    ebx,edx
  4d0078:	e8 c3 42 04 00       	call   0x514340
  4d007d:	83 c4 1c             	add    esp,0x1c
  4d0080:	8b d3                	mov    edx,ebx
  4d0082:	8b ce                	mov    ecx,esi
  4d0084:	ff 35 68 10 61 0a    	push   DWORD PTR ds:0xa611068
  4d008a:	53                   	push   ebx
  4d008b:	57                   	push   edi
  4d008c:	e8 af 42 04 00       	call   0x514340
  4d0091:	8b 55 fc             	mov    edx,DWORD PTR [ebp-0x4]
  4d0094:	83 c4 0c             	add    esp,0xc
  4d0097:	8b ce                	mov    ecx,esi
  4d0099:	ff 35 68 10 61 0a    	push   DWORD PTR ds:0xa611068
  4d009f:	53                   	push   ebx
  4d00a0:	56                   	push   esi
  4d00a1:	e8 9a 42 04 00       	call   0x514340
  4d00a6:	8b 55 fc             	mov    edx,DWORD PTR [ebp-0x4]
  4d00a9:	83 c4 0c             	add    esp,0xc
  4d00ac:	8b cf                	mov    ecx,edi
  4d00ae:	ff 35 68 10 61 0a    	push   DWORD PTR ds:0xa611068
  4d00b4:	53                   	push   ebx
  4d00b5:	57                   	push   edi
  4d00b6:	e8 85 42 04 00       	call   0x514340
  4d00bb:	8b 45 f8             	mov    eax,DWORD PTR [ebp-0x8]
  4d00be:	83 c4 0c             	add    esp,0xc
  4d00c1:	8b 7d f4             	mov    edi,DWORD PTR [ebp-0xc]
  4d00c4:	40                   	inc    eax
  4d00c5:	81 c7 e8 00 00 00    	add    edi,0xe8
  4d00cb:	89 45 f8             	mov    DWORD PTR [ebp-0x8],eax
  4d00ce:	89 7d f4             	mov    DWORD PTR [ebp-0xc],edi
  4d00d1:	3b 05 34 4a 35 06    	cmp    eax,DWORD PTR ds:0x6354a34
  4d00d7:	0f 8c 63 ff ff ff    	jl     0x4d0040
  4d00dd:	5f                   	pop    edi
  4d00de:	5e                   	pop    esi
  4d00df:	5b                   	pop    ebx
  4d00e0:	8b e5                	mov    esp,ebp
  4d00e2:	5d                   	pop    ebp
  4d00e3:	c3                   	ret

; Original PE VA 0x4d03e0..0x4d0404
  4d03e4:	89 7d f4             	mov    DWORD PTR [ebp-0xc],edi
  4d03e7:	3b 1d 34 4a 35 06    	cmp    ebx,DWORD PTR ds:0x6354a34
  4d03ed:	0f 8c bd fe ff ff    	jl     0x4d02b0
  4d03f3:	c7 05 c4 ba 5b 06 00 	mov    DWORD PTR ds:0x65bbac4,0x0
  4d03fa:	00 00 00 
  4d03fd:	5f                   	pop    edi
  4d03fe:	5e                   	pop    esi
  4d03ff:	5b                   	pop    ebx
  4d0400:	8b e5                	mov    esp,ebp
  4d0402:	5d                   	pop    ebp
  4d0403:	c3                   	ret

; Original PE VA 0x4fb938..0x4fba2a
  4fb938:	56                   	push   esi
  4fb939:	8d 45 90             	lea    eax,[ebp-0x70]
  4fb93c:	68 70 c6 58 00       	push   0x58c670
  4fb941:	50                   	push   eax
  4fb942:	e8 89 57 f0 ff       	call   0x4010d0
  4fb947:	0f 28 05 c0 da 5d 00 	movaps xmm0,XMMWORD PTR ds:0x5ddac0
  4fb94e:	8d 45 80             	lea    eax,[ebp-0x80]
  4fb951:	83 c4 0c             	add    esp,0xc
  4fb954:	0f 11 45 80          	movups XMMWORD PTR [ebp-0x80],xmm0
  4fb958:	50                   	push   eax
  4fb959:	ff 35 14 20 5c 0a    	push   DWORD PTR ds:0xa5c2014
  4fb95f:	50                   	push   eax
  4fb960:	ff 35 10 bb 5b 06    	push   DWORD PTR ds:0x65bbb10
  4fb966:	ff 15 04 c2 58 00    	call   DWORD PTR ds:0x58c204
  4fb96c:	6a 00                	push   0x0
  4fb96e:	6a 08                	push   0x8
  4fb970:	8d 45 90             	lea    eax,[ebp-0x70]
  4fb973:	ba 1f 02 00 00       	mov    edx,0x21f
  4fb978:	50                   	push   eax
  4fb979:	6a 37                	push   0x37
  4fb97b:	68 27 01 00 00       	push   0x127
  4fb980:	8d 4a d5             	lea    ecx,[edx-0x2b]
  4fb983:	e8 e8 a8 01 00       	call   0x516270
  4fb988:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4fb98d:	83 c4 24             	add    esp,0x24
  4fb990:	6a 64                	push   0x64
  4fb992:	6a 32                	push   0x32
  4fb994:	68 2c 01 00 00       	push   0x12c
  4fb999:	68 21 02 00 00       	push   0x221
  4fb99e:	68 f4 01 00 00       	push   0x1f4
  4fb9a3:	68 ff 00 00 00       	push   0xff
  4fb9a8:	68 ff 00 00 00       	push   0xff
  4fb9ad:	68 ff 00 00 00       	push   0xff
  4fb9b2:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4fb9b5:	ff 15 f8 c1 58 00    	call   DWORD PTR ds:0x58c1f8
  4fb9bb:	83 c4 10             	add    esp,0x10
  4fb9be:	ba 16 c6 58 00       	mov    edx,0x58c616
  4fb9c3:	8b c8                	mov    ecx,eax
  4fb9c5:	e8 c6 3d fd ff       	call   0x4cf790
  4fb9ca:	83 c4 14             	add    esp,0x14
  4fb9cd:	c7 05 9c 4a 35 06 01 	mov    DWORD PTR ds:0x6354a9c,0x1
  4fb9d4:	00 00 00 
  4fb9d7:	ba 0d 02 00 00       	mov    edx,0x20d
  4fb9dc:	c7 05 a0 4a 35 06 01 	mov    DWORD PTR ds:0x6354aa0,0x1
  4fb9e3:	00 00 00 
  4fb9e6:	b9 59 00 00 00       	mov    ecx,0x59
  4fb9eb:	68 64 f8 58 00       	push   0x58f864
  4fb9f0:	68 3a 02 00 00       	push   0x23a
  4fb9f5:	e8 f6 40 fd ff       	call   0x4cfaf0
  4fb9fa:	68 6c f8 58 00       	push   0x58f86c
  4fb9ff:	68 3a 02 00 00       	push   0x23a
  4fba04:	ba 49 02 00 00       	mov    edx,0x249
  4fba09:	b9 4e 00 00 00       	mov    ecx,0x4e
  4fba0e:	e8 dd 40 fd ff       	call   0x4cfaf0
  4fba13:	83 c4 10             	add    esp,0x10
  4fba16:	ba 16 c6 58 00       	mov    edx,0x58c616
  4fba1b:	b9 1b 00 00 00       	mov    ecx,0x1b
  4fba20:	e8 6b 3f fd ff       	call   0x4cf990
  4fba25:	e8 f6 56 fd ff       	call   0x4d1120

; Original PE VA 0x4fbb97..0x4fbc98
  4fbb97:	56                   	push   esi
  4fbb98:	8d 45 90             	lea    eax,[ebp-0x70]
  4fbb9b:	68 70 c6 58 00       	push   0x58c670
  4fbba0:	50                   	push   eax
  4fbba1:	e8 2a 55 f0 ff       	call   0x4010d0
  4fbba6:	0f 28 05 c0 da 5d 00 	movaps xmm0,XMMWORD PTR ds:0x5ddac0
  4fbbad:	8d 45 80             	lea    eax,[ebp-0x80]
  4fbbb0:	83 c4 0c             	add    esp,0xc
  4fbbb3:	0f 11 45 80          	movups XMMWORD PTR [ebp-0x80],xmm0
  4fbbb7:	50                   	push   eax
  4fbbb8:	ff 35 14 20 5c 0a    	push   DWORD PTR ds:0xa5c2014
  4fbbbe:	50                   	push   eax
  4fbbbf:	ff 35 10 bb 5b 06    	push   DWORD PTR ds:0x65bbb10
  4fbbc5:	ff 15 04 c2 58 00    	call   DWORD PTR ds:0x58c204
  4fbbcb:	6a 00                	push   0x0
  4fbbcd:	6a 08                	push   0x8
  4fbbcf:	8d 45 90             	lea    eax,[ebp-0x70]
  4fbbd2:	ba 1f 02 00 00       	mov    edx,0x21f
  4fbbd7:	50                   	push   eax
  4fbbd8:	6a 37                	push   0x37
  4fbbda:	68 27 01 00 00       	push   0x127
  4fbbdf:	8d 4a d5             	lea    ecx,[edx-0x2b]
  4fbbe2:	e8 89 a6 01 00       	call   0x516270
  4fbbe7:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4fbbec:	83 c4 24             	add    esp,0x24
  4fbbef:	6a 64                	push   0x64
  4fbbf1:	6a 32                	push   0x32
  4fbbf3:	68 2c 01 00 00       	push   0x12c
  4fbbf8:	68 21 02 00 00       	push   0x221
  4fbbfd:	68 f4 01 00 00       	push   0x1f4
  4fbc02:	68 ff 00 00 00       	push   0xff
  4fbc07:	68 ff 00 00 00       	push   0xff
  4fbc0c:	68 ff 00 00 00       	push   0xff
  4fbc11:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4fbc14:	ff 15 f8 c1 58 00    	call   DWORD PTR ds:0x58c1f8
  4fbc1a:	83 c4 10             	add    esp,0x10
  4fbc1d:	ba 16 c6 58 00       	mov    edx,0x58c616
  4fbc22:	8b c8                	mov    ecx,eax
  4fbc24:	e8 67 3b fd ff       	call   0x4cf790
  4fbc29:	83 c4 14             	add    esp,0x14
  4fbc2c:	c7 05 9c 4a 35 06 01 	mov    DWORD PTR ds:0x6354a9c,0x1
  4fbc33:	00 00 00 
  4fbc36:	ba 0d 02 00 00       	mov    edx,0x20d
  4fbc3b:	c7 05 a0 4a 35 06 01 	mov    DWORD PTR ds:0x6354aa0,0x1
  4fbc42:	00 00 00 
  4fbc45:	b9 59 00 00 00       	mov    ecx,0x59
  4fbc4a:	68 64 f8 58 00       	push   0x58f864
  4fbc4f:	68 3a 02 00 00       	push   0x23a
  4fbc54:	e8 97 3e fd ff       	call   0x4cfaf0
  4fbc59:	68 6c f8 58 00       	push   0x58f86c
  4fbc5e:	68 3a 02 00 00       	push   0x23a
  4fbc63:	ba 49 02 00 00       	mov    edx,0x249
  4fbc68:	b9 4e 00 00 00       	mov    ecx,0x4e
  4fbc6d:	e8 7e 3e fd ff       	call   0x4cfaf0
  4fbc72:	83 c4 10             	add    esp,0x10
  4fbc75:	ba 16 c6 58 00       	mov    edx,0x58c616
  4fbc7a:	b9 1b 00 00 00       	mov    ecx,0x1b
  4fbc7f:	e8 0c 3d fd ff       	call   0x4cf990
  4fbc84:	ba 16 c6 58 00       	mov    edx,0x58c616
  4fbc89:	b9 20 00 00 00       	mov    ecx,0x20
  4fbc8e:	e8 fd 3c fd ff       	call   0x4cf990
  4fbc93:	e8 88 54 fd ff       	call   0x4d1120

; Original PE VA 0x4d1167..0x4d121c
  4d1167:	0f 28 05 c0 da 5d 00 	movaps xmm0,XMMWORD PTR ds:0x5ddac0
  4d116e:	8d 85 e8 fb ff ff    	lea    eax,[ebp-0x418]
  4d1174:	50                   	push   eax
  4d1175:	ff 35 e0 1c 5c 0a    	push   DWORD PTR ds:0xa5c1ce0
  4d117b:	0f 11 85 e8 fb ff ff 	movups XMMWORD PTR [ebp-0x418],xmm0
  4d1182:	50                   	push   eax
  4d1183:	ff 35 10 bb 5b 06    	push   DWORD PTR ds:0x65bbb10
  4d1189:	ff 15 04 c2 58 00    	call   DWORD PTR ds:0x58c204
  4d118f:	83 c4 10             	add    esp,0x10
  4d1192:	83 3d 94 4b 35 06 00 	cmp    DWORD PTR ds:0x6354b94,0x0
  4d1199:	74 2b                	je     0x4d11c6
  4d119b:	a1 08 eb 34 06       	mov    eax,ds:0x634eb08
  4d11a0:	8b 0d 98 4b 35 06    	mov    ecx,DWORD PTR ds:0x6354b98
  4d11a6:	a3 bc 1c 5c 0a       	mov    ds:0xa5c1cbc,eax
  4d11ab:	89 0d 10 20 5c 0a    	mov    DWORD PTR ds:0xa5c2010,ecx
  4d11b1:	85 c0                	test   eax,eax
  4d11b3:	75 11                	jne    0x4d11c6
  4d11b5:	a1 34 56 35 06       	mov    eax,ds:0x6355634
  4d11ba:	33 d2                	xor    edx,edx
  4d11bc:	85 c9                	test   ecx,ecx
  4d11be:	0f 44 c2             	cmove  eax,edx
  4d11c1:	a3 34 56 35 06       	mov    ds:0x6355634,eax
  4d11c6:	89 1d f0 4d 35 06    	mov    DWORD PTR ds:0x6354df0,ebx
  4d11cc:	8b 35 7c c2 58 00    	mov    esi,DWORD PTR ds:0x58c27c
  4d11d2:	85 db                	test   ebx,ebx
  4d11d4:	0f 84 cb 00 00 00    	je     0x4d12a5
  4d11da:	33 d2                	xor    edx,edx
  4d11dc:	b9 c4 4a 35 06       	mov    ecx,0x6354ac4
  4d11e1:	e8 ea a6 f3 ff       	call   0x40b8d0
  4d11e6:	83 3d 94 4b 35 06 00 	cmp    DWORD PTR ds:0x6354b94,0x0
  4d11ed:	75 6b                	jne    0x4d125a
  4d11ef:	ff 35 2c 4a 35 06    	push   DWORD PTR ds:0x6354a2c
  4d11f5:	8b 15 24 4a 35 06    	mov    edx,DWORD PTR ds:0x6354a24
  4d11fb:	ff 35 28 4a 35 06    	push   DWORD PTR ds:0x6354a28
  4d1201:	8b 0d 20 4a 35 06    	mov    ecx,DWORD PTR ds:0x6354a20
  4d1207:	e8 a4 c9 03 00       	call   0x50dbb0
  4d120c:	8b 0d b0 4a 35 06    	mov    ecx,DWORD PTR ds:0x6354ab0
  4d1212:	83 c4 08             	add    esp,0x8
  4d1215:	33 d2                	xor    edx,edx
  4d1217:	e8 34 f4 ff ff       	call   0x4d0650

