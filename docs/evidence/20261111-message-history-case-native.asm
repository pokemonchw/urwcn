
/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe:     file format pei-i386


Disassembly of section .text:

004f6664 <.text+0xf5664>:
  4f6664:	80 3d 53 f4 17 02 00 	cmp    BYTE PTR ds:0x217f453,0x0
  4f666b:	8b 15 e8 c4 58 00    	mov    edx,DWORD PTR ds:0x58c4e8
  4f6671:	75 18                	jne    0x4f668b
  4f6673:	0f b6 05 b8 84 5a 06 	movzx  eax,BYTE PTR ds:0x65a84b8
  4f667a:	50                   	push   eax
  4f667b:	ff d2                	call   edx
  4f667d:	8b 15 e8 c4 58 00    	mov    edx,DWORD PTR ds:0x58c4e8
  4f6683:	83 c4 04             	add    esp,0x4
  4f6686:	a2 b8 84 5a 06       	mov    ds:0x65a84b8,al
  4f668b:	b9 b8 84 5a 06       	mov    ecx,0x65a84b8
  4f6690:	33 db                	xor    ebx,ebx
  4f6692:	8d 41 01             	lea    eax,[ecx+0x1]
  4f6695:	89 44 24 30          	mov    DWORD PTR [esp+0x30],eax
  4f6699:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [eax+0x0]
  4f66a0:	8a 01                	mov    al,BYTE PTR [ecx]
  4f66a2:	41                   	inc    ecx
  4f66a3:	84 c0                	test   al,al
  4f66a5:	75 f9                	jne    0x4f66a0
  4f66a7:	2b 4c 24 30          	sub    ecx,DWORD PTR [esp+0x30]
  4f66ab:	74 76                	je     0x4f6723
  4f66ad:	0f 1f 00             	nop    DWORD PTR [eax]
  4f66b0:	80 3d 53 f4 17 02 01 	cmp    BYTE PTR ds:0x217f453,0x1
  4f66b7:	0f 85 97 00 00 00    	jne    0x4f6754
  4f66bd:	33 ff                	xor    edi,edi
  4f66bf:	0f b6 83 b8 84 5a 06 	movzx  eax,BYTE PTR [ebx+0x65a84b8]
  4f66c6:	50                   	push   eax
  4f66c7:	68 34 9f 5a 00       	push   0x5a9f34
  4f66cc:	ff 15 48 c3 58 00    	call   DWORD PTR ds:0x58c348
  4f66d2:	83 c4 08             	add    esp,0x8
  4f66d5:	85 c0                	test   eax,eax
  4f66d7:	74 2b                	je     0x4f6704
  4f66d9:	80 bb b8 84 5a 06 2e 	cmp    BYTE PTR [ebx+0x65a84b8],0x2e
  4f66e0:	bf 01 00 00 00       	mov    edi,0x1
  4f66e5:	75 1d                	jne    0x4f6704
  4f66e7:	0f b6 83 b9 84 5a 06 	movzx  eax,BYTE PTR [ebx+0x65a84b9]
  4f66ee:	50                   	push   eax
  4f66ef:	68 3c 9f 5a 00       	push   0x5a9f3c
  4f66f4:	ff 15 48 c3 58 00    	call   DWORD PTR ds:0x58c348
  4f66fa:	33 c9                	xor    ecx,ecx
  4f66fc:	83 c4 08             	add    esp,0x8
  4f66ff:	85 c0                	test   eax,eax
  4f6701:	0f 45 f9             	cmovne edi,ecx
  4f6704:	b9 b8 84 5a 06       	mov    ecx,0x65a84b8
  4f6709:	43                   	inc    ebx
  4f670a:	8d 51 01             	lea    edx,[ecx+0x1]
  4f670d:	0f 1f 00             	nop    DWORD PTR [eax]
  4f6710:	8a 01                	mov    al,BYTE PTR [ecx]
  4f6712:	41                   	inc    ecx
  4f6713:	84 c0                	test   al,al
  4f6715:	75 f9                	jne    0x4f6710
  4f6717:	2b ca                	sub    ecx,edx
  4f6719:	8b 15 e8 c4 58 00    	mov    edx,DWORD PTR ds:0x58c4e8
  4f671f:	3b d9                	cmp    ebx,ecx
  4f6721:	72 8d                	jb     0x4f66b0
  4f6723:	c6 05 53 f4 17 02 00 	mov    BYTE PTR ds:0x217f453,0x0
  4f672a:	b9 b8 84 5a 06       	mov    ecx,0x65a84b8
  4f672f:	b8 c0 6a 5e 00       	mov    eax,0x5e6ac0
  4f6734:	8a 10                	mov    dl,BYTE PTR [eax]
  4f6736:	3a 11                	cmp    dl,BYTE PTR [ecx]
  4f6738:	75 54                	jne    0x4f678e
  4f673a:	84 d2                	test   dl,dl
  4f673c:	74 12                	je     0x4f6750
  4f673e:	8a 50 01             	mov    dl,BYTE PTR [eax+0x1]
  4f6741:	3a 51 01             	cmp    dl,BYTE PTR [ecx+0x1]
  4f6744:	75 48                	jne    0x4f678e
  4f6746:	83 c0 02             	add    eax,0x2
  4f6749:	83 c1 02             	add    ecx,0x2
  4f674c:	84 d2                	test   dl,dl
  4f674e:	75 e4                	jne    0x4f6734
  4f6750:	33 c0                	xor    eax,eax
  4f6752:	eb 3f                	jmp    0x4f6793
  4f6754:	85 ff                	test   edi,edi
  4f6756:	0f 84 63 ff ff ff    	je     0x4f66bf
  4f675c:	0f b6 83 b8 84 5a 06 	movzx  eax,BYTE PTR [ebx+0x65a84b8]
  4f6763:	50                   	push   eax
  4f6764:	ff d2                	call   edx
  4f6766:	83 c4 04             	add    esp,0x4
  4f6769:	88 83 b8 84 5a 06    	mov    BYTE PTR [ebx+0x65a84b8],al
  4f676f:	0f b6 c0             	movzx  eax,al
  4f6772:	50                   	push   eax
  4f6773:	68 1c 9f 5a 00       	push   0x5a9f1c
  4f6778:	ff 15 48 c3 58 00    	call   DWORD PTR ds:0x58c348
  4f677e:	83 c4 08             	add    esp,0x8
  4f6781:	8b f8                	mov    edi,eax
  4f6783:	f7 df                	neg    edi
  4f6785:	1b ff                	sbb    edi,edi
  4f6787:	f7 df                	neg    edi
  4f6789:	e9 76 ff ff ff       	jmp    0x4f6704
