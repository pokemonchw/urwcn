
/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe:     file format pei-i386


Disassembly of section .text:

0040f819 <.text+0xe819>:
  40f819:	83 3d bc 7a 61 00 01 	cmp    DWORD PTR ds:0x617abc,0x1
  40f820:	89 5d 88             	mov    DWORD PTR [ebp-0x78],ebx
  40f823:	0f 85 a6 00 00 00    	jne    0x40f8cf
  40f829:	33 db                	xor    ebx,ebx
  40f82b:	ff d7                	call   edi
  40f82d:	99                   	cdq
  40f82e:	b9 09 00 00 00       	mov    ecx,0x9
  40f833:	f7 f9                	idiv   ecx
  40f835:	8b f2                	mov    esi,edx
  40f837:	ff d7                	call   edi
  40f839:	99                   	cdq
  40f83a:	b9 09 00 00 00       	mov    ecx,0x9
  40f83f:	f7 f9                	idiv   ecx
  40f841:	43                   	inc    ebx
  40f842:	b8 ff ff ff ff       	mov    eax,0xffffffff
  40f847:	83 fb 0a             	cmp    ebx,0xa
  40f84a:	8b ca                	mov    ecx,edx
  40f84c:	0f 44 f0             	cmove  esi,eax
  40f84f:	3b ce                	cmp    ecx,esi
  40f851:	74 e4                	je     0x40f837
  40f853:	8d 50 02             	lea    edx,[eax+0x2]
  40f856:	89 0d b0 4a 35 06    	mov    DWORD PTR ds:0x6354ab0,ecx
  40f85c:	e8 ef 0d 0c 00       	call   0x4d0650
  40f861:	c7 45 8c 00 00 00 00 	mov    DWORD PTR [ebp-0x74],0x0
  40f868:	ff d7                	call   edi
  40f86a:	99                   	cdq
  40f86b:	b9 09 00 00 00       	mov    ecx,0x9
  40f870:	f7 f9                	idiv   ecx
  40f872:	8b f2                	mov    esi,edx
  40f874:	ff d7                	call   edi
  40f876:	99                   	cdq
  40f877:	b9 09 00 00 00       	mov    ecx,0x9
  40f87c:	f7 f9                	idiv   ecx
  40f87e:	8b 45 8c             	mov    eax,DWORD PTR [ebp-0x74]
  40f881:	40                   	inc    eax
  40f882:	8b da                	mov    ebx,edx
  40f884:	83 f8 0a             	cmp    eax,0xa
  40f887:	89 45 8c             	mov    DWORD PTR [ebp-0x74],eax
  40f88a:	b8 ff ff ff ff       	mov    eax,0xffffffff
  40f88f:	0f 44 f0             	cmove  esi,eax
  40f892:	3b de                	cmp    ebx,esi
  40f894:	74 de                	je     0x40f874
  40f896:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  40f89b:	68 80 00 00 00       	push   0x80
  40f8a0:	6a 57                	push   0x57
  40f8a2:	6a 57                	push   0x57
  40f8a4:	6a 57                	push   0x57
  40f8a6:	ff 70 04             	push   DWORD PTR [eax+0x4]
  40f8a9:	ff 15 f8 c1 58 00    	call   DWORD PTR ds:0x58c1f8
  40f8af:	83 c4 10             	add    esp,0x10
  40f8b2:	ba 1e 00 00 00       	mov    edx,0x1e
  40f8b7:	50                   	push   eax
  40f8b8:	68 e6 00 00 00       	push   0xe6
  40f8bd:	68 aa 00 00 00       	push   0xaa
  40f8c2:	8d 4a f1             	lea    ecx,[edx-0xf]
  40f8c5:	e8 36 e0 0f 00       	call   0x50d900
  40f8ca:	83 c4 10             	add    esp,0x10
  40f8cd:	eb 07                	jmp    0x40f8d6
  40f8cf:	e8 4c 18 0c 00       	call   0x4d1120
  40f8d4:	8b d8                	mov    ebx,eax
  40f8d6:	83 fb 64             	cmp    ebx,0x64
  40f8d9:	7d 57                	jge    0x40f932
  40f8db:	85 db                	test   ebx,ebx
  40f8dd:	78 53                	js     0x40f932
  40f8df:	69 c3 e8 00 00 00    	imul   eax,ebx,0xe8
  40f8e5:	83 b8 d8 ef 34 06 52 	cmp    DWORD PTR [eax+0x634efd8],0x52
  40f8ec:	75 44                	jne    0x40f932
  40f8ee:	c7 45 8c 00 00 00 00 	mov    DWORD PTR [ebp-0x74],0x0
  40f8f5:	ff d7                	call   edi
  40f8f7:	99                   	cdq
  40f8f8:	b9 0a 00 00 00       	mov    ecx,0xa
  40f8fd:	f7 f9                	idiv   ecx
  40f8ff:	8b f2                	mov    esi,edx
  40f901:	ff d7                	call   edi
  40f903:	99                   	cdq
  40f904:	b9 0a 00 00 00       	mov    ecx,0xa
  40f909:	f7 f9                	idiv   ecx
  40f90b:	8b 45 8c             	mov    eax,DWORD PTR [ebp-0x74]
  40f90e:	40                   	inc    eax
  40f90f:	8b da                	mov    ebx,edx
  40f911:	3b c1                	cmp    eax,ecx
  40f913:	89 45 8c             	mov    DWORD PTR [ebp-0x74],eax
  40f916:	b8 ff ff ff ff       	mov    eax,0xffffffff
  40f91b:	0f 44 f0             	cmove  esi,eax
  40f91e:	3b de                	cmp    ebx,esi
  40f920:	74 df                	je     0x40f901
  40f922:	8d 51 f7             	lea    edx,[ecx-0x9]
  40f925:	89 1d b0 4a 35 06    	mov    DWORD PTR ds:0x6354ab0,ebx
  40f92b:	8b cb                	mov    ecx,ebx
  40f92d:	e8 1e 0d 0c 00       	call   0x4d0650
  40f932:	83 fb ff             	cmp    ebx,0xffffffff
  40f935:	0f 84 3a fd ff ff    	je     0x40f675
  40f93b:	83 fb 64             	cmp    ebx,0x64
  40f93e:	0f                   	.byte 0xf
  40f93f:	8d                   	.byte 0x8d
