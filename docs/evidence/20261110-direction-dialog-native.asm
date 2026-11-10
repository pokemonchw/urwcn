
/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe:     file format pei-i386


Disassembly of section .text:

004f7820 <.text+0xf6820>:
  4f7820:	55                   	push   ebp
  4f7821:	8b ec                	mov    ebp,esp
  4f7823:	83 e4 c0             	and    esp,0xffffffc0
  4f7826:	81 ec b4 00 00 00    	sub    esp,0xb4
  4f782c:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  4f7831:	33 c4                	xor    eax,esp
  4f7833:	89 84 24 b0 00 00 00 	mov    DWORD PTR [esp+0xb0],eax
  4f783a:	53                   	push   ebx
  4f783b:	56                   	push   esi
  4f783c:	57                   	push   edi
  4f783d:	33 db                	xor    ebx,ebx
  4f783f:	88 4c 24 16          	mov    BYTE PTR [esp+0x16],cl
  4f7843:	8b fa                	mov    edi,edx
  4f7845:	c7 44 24 10 00 00 00 	mov    DWORD PTR [esp+0x10],0x0
  4f784c:	00 
  4f784d:	33 f6                	xor    esi,esi
  4f784f:	89 7c 24 24          	mov    DWORD PTR [esp+0x24],edi
  4f7853:	c7 44 24 1c 18 fc ff 	mov    DWORD PTR [esp+0x1c],0xfffffc18
  4f785a:	ff 
  4f785b:	39 1d 9c 87 5e 00    	cmp    DWORD PTR ds:0x5e879c,ebx
  4f7861:	75 10                	jne    0x4f7873
  4f7863:	b9 7c d5 59 00       	mov    ecx,0x59d57c
  4f7868:	89 1d d8 bc 5b 06    	mov    DWORD PTR ds:0x65bbcd8,ebx
  4f786e:	e8 7d 38 01 00       	call   0x50b0f0
  4f7873:	68 3c 56 35 06       	push   0x635563c
  4f7878:	68 38 56 35 06       	push   0x6355638
  4f787d:	ff 35 30 bb 5b 06    	push   DWORD PTR ds:0x65bbb30
  4f7883:	c6 05 c9 e3 17 02 01 	mov    BYTE PTR ds:0x217e3c9,0x1
  4f788a:	ff 15 30 c2 58 00    	call   DWORD PTR ds:0x58c230
  4f7890:	83 c4 0c             	add    esp,0xc
  4f7893:	68 94 0e 15 06       	push   0x6150e94
  4f7898:	68 bc 4b 35 06       	push   0x6354bbc
  4f789d:	ff 35 30 bb 5b 06    	push   DWORD PTR ds:0x65bbb30
  4f78a3:	ff 15 50 c2 58 00    	call   DWORD PTR ds:0x58c250
  4f78a9:	83 c4 0c             	add    esp,0xc
  4f78ac:	e8 cf fd ff ff       	call   0x4f7680
  4f78b1:	8a 44 24 16          	mov    al,BYTE PTR [esp+0x16]
  4f78b5:	8d 54 24 40          	lea    edx,[esp+0x40]
  4f78b9:	24 01                	and    al,0x1
  4f78bb:	b9 70 43 59 00       	mov    ecx,0x594370
  4f78c0:	88 44 24 17          	mov    BYTE PTR [esp+0x17],al
  4f78c4:	74 21                	je     0x4f78e7
  4f78c6:	0f 28 05 f0 d9 5d 00 	movaps xmm0,XMMWORD PTR ds:0x5dd9f0
  4f78cd:	0f 11 44 24 40       	movups XMMWORD PTR [esp+0x40],xmm0
  4f78d2:	e8 69 4c 01 00       	call   0x50c540
  4f78d7:	6a 00                	push   0x0
  4f78d9:	6a 28                	push   0x28
  4f78db:	68 64 9f 5a 00       	push   0x5a9f64
  4f78e0:	68 96 00 00 00       	push   0x96
  4f78e5:	eb 22                	jmp    0x4f7909
  4f78e7:	0f 28 05 e0 d9 5d 00 	movaps xmm0,XMMWORD PTR ds:0x5dd9e0
  4f78ee:	0f 11 44 24 40       	movups XMMWORD PTR [esp+0x40],xmm0
  4f78f3:	e8 48 4c 01 00       	call   0x50c540
  4f78f8:	6a 00                	push   0x0
  4f78fa:	6a 28                	push   0x28
  4f78fc:	8b cf                	mov    ecx,edi
  4f78fe:	e8 ad c4 fd ff       	call   0x4d3db0
  4f7903:	50                   	push   eax
  4f7904:	68 8c 00 00 00       	push   0x8c
  4f7909:	68 1e 01 00 00       	push   0x11e
  4f790e:	ba be 00 00 00       	mov    edx,0xbe
  4f7913:	b9 f7 01 00 00       	mov    ecx,0x1f7
  4f7918:	e8 53 e9 01 00       	call   0x516270
  4f791d:	83 c4 14             	add    esp,0x14
  4f7920:	ba dc 00 00 00       	mov    edx,0xdc
  4f7925:	b9 01 02 00 00       	mov    ecx,0x201
  4f792a:	68 74 9f 5a 00       	push   0x5a9f74
  4f792f:	e8 4c cd 01 00       	call   0x514680
  4f7934:	83 c4 04             	add    esp,0x4
  4f7937:	8d 44 24 50          	lea    eax,[esp+0x50]
  4f793b:	6a 18                	push   0x18
  4f793d:	68 dc d6 58 00       	push   0x58d6dc
  4f7942:	50                   	push   eax
  4f7943:	e8 88 97 f0 ff       	call   0x4010d0
  4f7948:	83 c4 0c             	add    esp,0xc
  4f794b:	8d 44 24 50          	lea    eax,[esp+0x50]
  4f794f:	ba dc 00 00 00       	mov    edx,0xdc
  4f7954:	b9 15 02 00 00       	mov    ecx,0x215
  4f7959:	50                   	push   eax
  4f795a:	e8 21 cd 01 00       	call   0x514680
  4f795f:	83 c4 04             	add    esp,0x4
  4f7962:	ba dc 00 00 00       	mov    edx,0xdc
  4f7967:	b9 29 02 00 00       	mov    ecx,0x229
  4f796c:	68 78 9f 5a 00       	push   0x5a9f78
  4f7971:	e8 0a cd 01 00       	call   0x514680
  4f7976:	83 c4 04             	add    esp,0x4
  4f7979:	8d 44 24 50          	lea    eax,[esp+0x50]
  4f797d:	6a 1b                	push   0x1b
  4f797f:	68 dc d6 58 00       	push   0x58d6dc
  4f7984:	50                   	push   eax
  4f7985:	e8 46 97 f0 ff       	call   0x4010d0
  4f798a:	83 c4 0c             	add    esp,0xc
  4f798d:	8d 44 24 50          	lea    eax,[esp+0x50]
  4f7991:	ba f0 00 00 00       	mov    edx,0xf0
  4f7996:	b9 01 02 00 00       	mov    ecx,0x201
  4f799b:	50                   	push   eax
  4f799c:	e8 df cc 01 00       	call   0x514680
  4f79a1:	83 c4 04             	add    esp,0x4
  4f79a4:	8d 44 24 50          	lea    eax,[esp+0x50]
  4f79a8:	6a 1a                	push   0x1a
  4f79aa:	68 dc d6 58 00       	push   0x58d6dc
  4f79af:	50                   	push   eax
  4f79b0:	e8 1b 97 f0 ff       	call   0x4010d0
  4f79b5:	83 c4 0c             	add    esp,0xc
  4f79b8:	8d 44 24 50          	lea    eax,[esp+0x50]
  4f79bc:	ba f0 00 00 00       	mov    edx,0xf0
  4f79c1:	b9 29 02 00 00       	mov    ecx,0x229
  4f79c6:	50                   	push   eax
  4f79c7:	e8 b4 cc 01 00       	call   0x514680
  4f79cc:	8a 44 24 1a          	mov    al,BYTE PTR [esp+0x1a]
  4f79d0:	83 c4 04             	add    esp,0x4
  4f79d3:	24 10                	and    al,0x10
  4f79d5:	88 44 24 2b          	mov    BYTE PTR [esp+0x2b],al
  4f79d9:	74 17                	je     0x4f79f2
  4f79db:	68 f4 3e 5a 00       	push   0x5a3ef4
  4f79e0:	ba f0 00 00 00       	mov    edx,0xf0
  4f79e5:	b9 15 02 00 00       	mov    ecx,0x215
  4f79ea:	e8 91 cc 01 00       	call   0x514680
  4f79ef:	83 c4 04             	add    esp,0x4
  4f79f2:	68 9c c6 58 00       	push   0x58c69c
  4f79f7:	ba 04 01 00 00       	mov    edx,0x104
  4f79fc:	b9 01 02 00 00       	mov    ecx,0x201
  4f7a01:	e8 7a cc 01 00       	call   0x514680
  4f7a06:	83 c4 04             	add    esp,0x4
  4f7a09:	8d 44 24 50          	lea    eax,[esp+0x50]
  4f7a0d:	6a 19                	push   0x19
  4f7a0f:	68 dc d6 58 00       	push   0x58d6dc
  4f7a14:	50                   	push   eax
  4f7a15:	e8 b6 96 f0 ff       	call   0x4010d0
  4f7a1a:	83 c4 0c             	add    esp,0xc
  4f7a1d:	8d 44 24 50          	lea    eax,[esp+0x50]
  4f7a21:	ba 04 01 00 00       	mov    edx,0x104
  4f7a26:	b9 15 02 00 00       	mov    ecx,0x215
  4f7a2b:	50                   	push   eax
  4f7a2c:	e8 4f cc 01 00       	call   0x514680
  4f7a31:	83 c4 04             	add    esp,0x4
  4f7a34:	ba 04 01 00 00       	mov    edx,0x104
  4f7a39:	b9 29 02 00 00       	mov    ecx,0x229
  4f7a3e:	68 7c 9f 5a 00       	push   0x5a9f7c
  4f7a43:	e8 38 cc 01 00       	call   0x514680
  4f7a48:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4f7a4d:	83 c4 04             	add    esp,0x4
  4f7a50:	8b 3d f8 c1 58 00    	mov    edi,DWORD PTR ds:0x58c1f8
  4f7a56:	68 de 00 00 00       	push   0xde
  4f7a5b:	68 c4 00 00 00       	push   0xc4
  4f7a60:	68 b0 00 00 00       	push   0xb0
  4f7a65:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4f7a68:	ff d7                	call   edi
  4f7a6a:	68 c8 50 59 00       	push   0x5950c8
  4f7a6f:	ba 27 01 00 00       	mov    edx,0x127
  4f7a74:	a3 c4 ba 5b 06       	mov    ds:0x65bbac4,eax
  4f7a79:	b9 01 02 00 00       	mov    ecx,0x201
  4f7a7e:	c7 05 54 ba 5b 06 01 	mov    DWORD PTR ds:0x65bba54,0x1
  4f7a85:	00 00 00 
  4f7a88:	e8 f3 cb 01 00       	call   0x514680
  4f7a8d:	83 c4 14             	add    esp,0x14
  4f7a90:	38 5c 24 17          	cmp    BYTE PTR [esp+0x17],bl
  4f7a94:	74 28                	je     0x4f7abe
  4f7a96:	68 80 9f 5a 00       	push   0x5a9f80
  4f7a9b:	ba 27 01 00 00       	mov    edx,0x127
  4f7aa0:	b9 51 02 00 00       	mov    ecx,0x251
  4f7aa5:	e8 d6 cb 01 00       	call   0x514680
  4f7aaa:	83 c4 04             	add    esp,0x4
  4f7aad:	39 1d c0 9b 5a 06    	cmp    DWORD PTR ds:0x65a9bc0,ebx
  4f7ab3:	74 09                	je     0x4f7abe
  4f7ab5:	51                   	push   ecx
  4f7ab6:	e8 65 cf 01 00       	call   0x514a20
  4f7abb:	83 c4 04             	add    esp,0x4
  4f7abe:	8a 44 24 16          	mov    al,BYTE PTR [esp+0x16]
  4f7ac2:	24 02                	and    al,0x2
  4f7ac4:	89 1d 54 ba 5b 06    	mov    DWORD PTR ds:0x65bba54,ebx
  4f7aca:	88 44 24 15          	mov    BYTE PTR [esp+0x15],al
  4f7ace:	74 71                	je     0x4f7b41
  4f7ad0:	ff 74 24 24          	push   DWORD PTR [esp+0x24]
  4f7ad4:	8d 44 24 54          	lea    eax,[esp+0x54]
  4f7ad8:	68 b4 9f 5a 00       	push   0x5a9fb4
  4f7add:	50                   	push   eax
  4f7ade:	e8 ed 95 f0 ff       	call   0x4010d0
  4f7ae3:	83 c4 0c             	add    esp,0xc
  4f7ae6:	8d 54 24 50          	lea    edx,[esp+0x50]
  4f7aea:	b9 01 00 00 00       	mov    ecx,0x1
  4f7aef:	e8 0c a8 06 00       	call   0x562300
  4f7af4:	ba c0 9f 5a 00       	mov    edx,0x5a9fc0
  4f7af9:	33 c9                	xor    ecx,ecx
  4f7afb:	e8 00 a8 06 00       	call   0x562300
  4f7b00:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4f7b05:	6a 01                	push   0x1
  4f7b07:	68 ff 00 00 00       	push   0xff
  4f7b0c:	68 ff 00 00 00       	push   0xff
  4f7b11:	68 ff 00 00 00       	push   0xff
  4f7b16:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4f7b19:	ff d7                	call   edi
  4f7b1b:	83 c4 10             	add    esp,0x10
  4f7b1e:	ba dc 00 00 00       	mov    edx,0xdc
  4f7b23:	b9 47 02 00 00       	mov    ecx,0x247
  4f7b28:	50                   	push   eax
  4f7b29:	68 c8 00 00 00       	push   0xc8
  4f7b2e:	68 c3 00 00 00       	push   0xc3
  4f7b33:	e8 08 70 01 00       	call   0x50eb40
  4f7b38:	83 c4 10             	add    esp,0x10
  4f7b3b:	33 ff                	xor    edi,edi
  4f7b3d:	33 c0                	xor    eax,eax
  4f7b3f:	eb 08                	jmp    0x4f7b49
  4f7b41:	8b 7c 24 30          	mov    edi,DWORD PTR [esp+0x30]
  4f7b45:	8b 44 24 30          	mov    eax,DWORD PTR [esp+0x30]
  4f7b49:	89 44 24 18          	mov    DWORD PTR [esp+0x18],eax
  4f7b4d:	38 5c 24 17          	cmp    BYTE PTR [esp+0x17],bl
  4f7b51:	0f 84 0c 01 00 00    	je     0x4f7c63
  4f7b57:	ba 30 a0 5a 00       	mov    edx,0x5aa030
  4f7b5c:	b9 01 00 00 00       	mov    ecx,0x1
  4f7b61:	e8 9a a7 06 00       	call   0x562300
  4f7b66:	ba 74 a0 5a 00       	mov    edx,0x5aa074
  4f7b6b:	33 c9                	xor    ecx,ecx
  4f7b6d:	e8 8e a7 06 00       	call   0x562300
  4f7b72:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4f7b77:	6a 01                	push   0x1
  4f7b79:	68 ff 00 00 00       	push   0xff
  4f7b7e:	68 ff 00 00 00       	push   0xff
  4f7b83:	68 ff 00 00 00       	push   0xff
  4f7b88:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4f7b8b:	ff 15 f8 c1 58 00    	call   DWORD PTR ds:0x58c1f8
  4f7b91:	83 c4 10             	add    esp,0x10
  4f7b94:	ba dc 00 00 00       	mov    edx,0xdc
  4f7b99:	b9 47 02 00 00       	mov    ecx,0x247
  4f7b9e:	50                   	push   eax
  4f7b9f:	68 c8 00 00 00       	push   0xc8
  4f7ba4:	68 b4 00 00 00       	push   0xb4
  4f7ba9:	e8 92 6f 01 00       	call   0x50eb40
  4f7bae:	a1 9c 1c 6d 0a       	mov    eax,ds:0xa6d1c9c
  4f7bb3:	83 c4 10             	add    esp,0x10
  4f7bb6:	3b 05 8c 61 5a 06    	cmp    eax,DWORD PTR ds:0x65a618c
  4f7bbc:	75 21                	jne    0x4f7bdf
  4f7bbe:	a1 40 bd 72 0a       	mov    eax,ds:0xa72bd40
  4f7bc3:	3b 05 88 96 5a 06    	cmp    eax,DWORD PTR ds:0x65a9688
  4f7bc9:	75 14                	jne    0x4f7bdf
  4f7bcb:	8b 1d c0 8c 5a 06    	mov    ebx,DWORD PTR ds:0x65a8cc0
  4f7bd1:	8b 35 90 96 5a 06    	mov    esi,DWORD PTR ds:0x65a9690
  4f7bd7:	8b 15 c0 6e 5e 00    	mov    edx,DWORD PTR ds:0x5e6ec0
  4f7bdd:	eb 1b                	jmp    0x4f7bfa
  4f7bdf:	33 db                	xor    ebx,ebx
  4f7be1:	ba 18 fc ff ff       	mov    edx,0xfffffc18
  4f7be6:	33 f6                	xor    esi,esi
  4f7be8:	89 1d c0 8c 5a 06    	mov    DWORD PTR ds:0x65a8cc0,ebx
  4f7bee:	89 35 90 96 5a 06    	mov    DWORD PTR ds:0x65a9690,esi
  4f7bf4:	89 15 c0 6e 5e 00    	mov    DWORD PTR ds:0x5e6ec0,edx
  4f7bfa:	81 fa 18 fc ff ff    	cmp    edx,0xfffffc18
  4f7c00:	74 49                	je     0x4f7c4b
  4f7c02:	8b 0d c0 9b 5a 06    	mov    ecx,DWORD PTR ds:0x65a9bc0
  4f7c08:	85 c9                	test   ecx,ecx
  4f7c0a:	74 3f                	je     0x4f7c4b
  4f7c0c:	33 c0                	xor    eax,eax
  4f7c0e:	85 c9                	test   ecx,ecx
  4f7c10:	7e 39                	jle    0x4f7c4b
  4f7c12:	39 14 85 f8 90 5a 06 	cmp    DWORD PTR [eax*4+0x65a90f8],edx
  4f7c19:	74 07                	je     0x4f7c22
  4f7c1b:	40                   	inc    eax
  4f7c1c:	3b c1                	cmp    eax,ecx
  4f7c1e:	7c f2                	jl     0x4f7c12
  4f7c20:	eb 29                	jmp    0x4f7c4b
  4f7c22:	8b 34 85 f8 90 5a 06 	mov    esi,DWORD PTR [eax*4+0x65a90f8]
  4f7c29:	8b ce                	mov    ecx,esi
  4f7c2b:	89 44 24 1c          	mov    DWORD PTR [esp+0x1c],eax
  4f7c2f:	e8 3c 14 f2 ff       	call   0x419070
  4f7c34:	8b d8                	mov    ebx,eax
  4f7c36:	8b ce                	mov    ecx,esi
  4f7c38:	2b 1d 9c 1c 6d 0a    	sub    ebx,DWORD PTR ds:0xa6d1c9c
  4f7c3e:	e8 7d 14 f2 ff       	call   0x4190c0
  4f7c43:	8b f0                	mov    esi,eax
  4f7c45:	2b 35 40 bd 72 0a    	sub    esi,DWORD PTR ds:0xa72bd40
  4f7c4b:	8b 0d 9c 1c 6d 0a    	mov    ecx,DWORD PTR ds:0xa6d1c9c
  4f7c51:	89 0d 8c 61 5a 06    	mov    DWORD PTR ds:0x65a618c,ecx
  4f7c57:	8b 0d 40 bd 72 0a    	mov    ecx,DWORD PTR ds:0xa72bd40
  4f7c5d:	89 0d 88 96 5a 06    	mov    DWORD PTR ds:0x65a9688,ecx
  4f7c63:	f6 44 24 16 08       	test   BYTE PTR [esp+0x16],0x8
  4f7c68:	74 6f                	je     0x4f7cd9
  4f7c6a:	8b 15 40 bd 72 0a    	mov    edx,DWORD PTR ds:0xa72bd40
  4f7c70:	8b 0d 9c 1c 6d 0a    	mov    ecx,DWORD PTR ds:0xa6d1c9c
  4f7c76:	8d 14 32             	lea    edx,[edx+esi*1]
  4f7c79:	8d 0c 19             	lea    ecx,[ecx+ebx*1]
  4f7c7c:	e8 9f 14 f2 ff       	call   0x419120
  4f7c81:	8b 0d c0 9b 5a 06    	mov    ecx,DWORD PTR ds:0x65a9bc0
  4f7c87:	8b d0                	mov    edx,eax
  4f7c89:	85 d2                	test   edx,edx
  4f7c8b:	79 32                	jns    0x4f7cbf
  4f7c8d:	85 c9                	test   ecx,ecx
  4f7c8f:	74 2e                	je     0x4f7cbf
  4f7c91:	33 c9                	xor    ecx,ecx
  4f7c93:	89 4c 24 1c          	mov    DWORD PTR [esp+0x1c],ecx
  4f7c97:	8b 0d f8 90 5a 06    	mov    ecx,DWORD PTR ds:0x65a90f8
  4f7c9d:	e8 ce 13 f2 ff       	call   0x419070
  4f7ca2:	8b 0d f8 90 5a 06    	mov    ecx,DWORD PTR ds:0x65a90f8
  4f7ca8:	8b d8                	mov    ebx,eax
  4f7caa:	2b 1d 9c 1c 6d 0a    	sub    ebx,DWORD PTR ds:0xa6d1c9c
  4f7cb0:	e8 0b 14 f2 ff       	call   0x4190c0
  4f7cb5:	8b f0                	mov    esi,eax
  4f7cb7:	2b 35 40 bd 72 0a    	sub    esi,DWORD PTR ds:0xa72bd40
  4f7cbd:	eb 1a                	jmp    0x4f7cd9
  4f7cbf:	33 c0                	xor    eax,eax
  4f7cc1:	85 c9                	test   ecx,ecx
  4f7cc3:	7e 14                	jle    0x4f7cd9
  4f7cc5:	39 14 85 f8 90 5a 06 	cmp    DWORD PTR [eax*4+0x65a90f8],edx
  4f7ccc:	74 07                	je     0x4f7cd5
  4f7cce:	40                   	inc    eax
  4f7ccf:	3b c1                	cmp    eax,ecx
  4f7cd1:	7c f2                	jl     0x4f7cc5
  4f7cd3:	eb 04                	jmp    0x4f7cd9
  4f7cd5:	89 44 24 1c          	mov    DWORD PTR [esp+0x1c],eax
  4f7cd9:	a1 d4 b5 5b 06       	mov    eax,ds:0x65bb5d4
  4f7cde:	8b 0d d8 b5 5b 06    	mov    ecx,DWORD PTR ds:0x65bb5d8
  4f7ce4:	0f 1f 40 00          	nop    DWORD PTR [eax+0x0]
  4f7ce8:	0f 1f 84 00 00 00 00 	nop    DWORD PTR [eax+eax*1+0x0]
  4f7cef:	00 
  4f7cf0:	83 3d 5c ba 5b 06 00 	cmp    DWORD PTR ds:0x65bba5c,0x0
  4f7cf7:	8b 15 d8 bc 5b 06    	mov    edx,DWORD PTR ds:0x65bbcd8
  4f7cfd:	89 54 24 24          	mov    DWORD PTR [esp+0x24],edx
  4f7d01:	8b 15 50 ba 5b 06    	mov    edx,DWORD PTR ds:0x65bba50
  4f7d07:	89 54 24 38          	mov    DWORD PTR [esp+0x38],edx
  4f7d0b:	75 36                	jne    0x4f7d43
  4f7d0d:	c7 05 d8 bc 5b 06 01 	mov    DWORD PTR ds:0x65bbcd8,0x1
  4f7d14:	00 00 00 
  4f7d17:	c7 05 50 ba 5b 06 01 	mov    DWORD PTR ds:0x65bba50,0x1
  4f7d1e:	00 00 00 
  4f7d21:	e8 fa 39 01 00       	call   0x50b720
  4f7d26:	8b 44 24 24          	mov    eax,DWORD PTR [esp+0x24]
  4f7d2a:	8b 0d d8 b5 5b 06    	mov    ecx,DWORD PTR ds:0x65bb5d8
  4f7d30:	a3 d8 bc 5b 06       	mov    ds:0x65bbcd8,eax
  4f7d35:	8b 44 24 38          	mov    eax,DWORD PTR [esp+0x38]
  4f7d39:	a3 50 ba 5b 06       	mov    ds:0x65bba50,eax
  4f7d3e:	a1 d4 b5 5b 06       	mov    eax,ds:0x65bb5d4
  4f7d43:	8a 54 24 17          	mov    dl,BYTE PTR [esp+0x17]
  4f7d47:	89 5c 24 3c          	mov    DWORD PTR [esp+0x3c],ebx
  4f7d4b:	89 74 24 38          	mov    DWORD PTR [esp+0x38],esi
  4f7d4f:	84 d2                	test   dl,dl
  4f7d51:	74 3c                	je     0x4f7d8f
  4f7d53:	3b d8                	cmp    ebx,eax
  4f7d55:	7e 0a                	jle    0x4f7d61
  4f7d57:	8b d8                	mov    ebx,eax
  4f7d59:	c7 44 24 1c 18 fc ff 	mov    DWORD PTR [esp+0x1c],0xfffffc18
  4f7d60:	ff 
  4f7d61:	3b f1                	cmp    esi,ecx
  4f7d63:	7e 0a                	jle    0x4f7d6f
  4f7d65:	8b f1                	mov    esi,ecx
  4f7d67:	c7 44 24 1c 18 fc ff 	mov    DWORD PTR [esp+0x1c],0xfffffc18
  4f7d6e:	ff 
  4f7d6f:	f7 d9                	neg    ecx
  4f7d71:	3b f1                	cmp    esi,ecx
  4f7d73:	7d 0a                	jge    0x4f7d7f
  4f7d75:	8b f1                	mov    esi,ecx
  4f7d77:	c7 44 24 1c 18 fc ff 	mov    DWORD PTR [esp+0x1c],0xfffffc18
  4f7d7e:	ff 
  4f7d7f:	f7 d8                	neg    eax
  4f7d81:	3b d8                	cmp    ebx,eax
  4f7d83:	7d 0a                	jge    0x4f7d8f
  4f7d85:	8b d8                	mov    ebx,eax
  4f7d87:	c7 44 24 1c 18 fc ff 	mov    DWORD PTR [esp+0x1c],0xfffffc18
  4f7d8e:	ff 
  4f7d8f:	8b 0d 9c 1c 6d 0a    	mov    ecx,DWORD PTR ds:0xa6d1c9c
  4f7d95:	a1 40 bd 72 0a       	mov    eax,ds:0xa72bd40
  4f7d9a:	03 cb                	add    ecx,ebx
  4f7d9c:	03 c6                	add    eax,esi
  4f7d9e:	89 4c 24 20          	mov    DWORD PTR [esp+0x20],ecx
  4f7da2:	89 44 24 2c          	mov    DWORD PTR [esp+0x2c],eax
  4f7da6:	84 d2                	test   dl,dl
  4f7da8:	75 08                	jne    0x4f7db2
  4f7daa:	85 db                	test   ebx,ebx
  4f7dac:	75 04                	jne    0x4f7db2
  4f7dae:	85 f6                	test   esi,esi
  4f7db0:	74 1d                	je     0x4f7dcf
  4f7db2:	51                   	push   ecx
  4f7db3:	8b d0                	mov    edx,eax
  4f7db5:	e8 e6 f1 ff ff       	call   0x4f6fa0
  4f7dba:	8b 44 24 24          	mov    eax,DWORD PTR [esp+0x24]
  4f7dbe:	83 c4 04             	add    esp,0x4
  4f7dc1:	a3 54 54 78 02       	mov    ds:0x2785454,eax
  4f7dc6:	8b 44 24 2c          	mov    eax,DWORD PTR [esp+0x2c]
  4f7dca:	a3 94 68 d8 02       	mov    ds:0x2d86894,eax
  4f7dcf:	e8 ec 91 fd ff       	call   0x4d0fc0
  4f7dd4:	e8 17 be fd ff       	call   0x4d3bf0
  4f7dd9:	3d 2f 04 00 00       	cmp    eax,0x42f
  4f7dde:	0f 8f 76 02 00 00    	jg     0x4f805a
  4f7de4:	0f 84 41 02 00 00    	je     0x4f802b
  4f7dea:	40                   	inc    eax
  4f7deb:	83 f8 3e             	cmp    eax,0x3e
  4f7dee:	0f 87 9b 05 00 00    	ja     0x4f838f
  4f7df4:	0f b6 80 b4 86 4f 00 	movzx  eax,BYTE PTR [eax+0x4f86b4]
  4f7dfb:	ff 24 85 78 86 4f 00 	jmp    DWORD PTR [eax*4+0x4f8678]
  4f7e02:	8b 0d c0 9b 5a 06    	mov    ecx,DWORD PTR ds:0x65a9bc0
  4f7e08:	85 c9                	test   ecx,ecx
  4f7e0a:	0f 84 7f 05 00 00    	je     0x4f838f
  4f7e10:	80 7c 24 17 00       	cmp    BYTE PTR [esp+0x17],0x0
  4f7e15:	0f 84 74 05 00 00    	je     0x4f838f
  4f7e1b:	8b 44 24 1c          	mov    eax,DWORD PTR [esp+0x1c]
  4f7e1f:	3d 18 fc ff ff       	cmp    eax,0xfffffc18
  4f7e24:	75 04                	jne    0x4f7e2a
  4f7e26:	33 c0                	xor    eax,eax
  4f7e28:	eb 08                	jmp    0x4f7e32
  4f7e2a:	40                   	inc    eax
  4f7e2b:	33 d2                	xor    edx,edx
  4f7e2d:	3b c1                	cmp    eax,ecx
  4f7e2f:	0f 44 c2             	cmove  eax,edx
  4f7e32:	8b 34 85 f8 90 5a 06 	mov    esi,DWORD PTR [eax*4+0x65a90f8]
  4f7e39:	8b ce                	mov    ecx,esi
  4f7e3b:	89 44 24 1c          	mov    DWORD PTR [esp+0x1c],eax
  4f7e3f:	e8 2c 12 f2 ff       	call   0x419070
  4f7e44:	8b d8                	mov    ebx,eax
  4f7e46:	8b ce                	mov    ecx,esi
  4f7e48:	2b 1d 9c 1c 6d 0a    	sub    ebx,DWORD PTR ds:0xa6d1c9c
  4f7e4e:	e8 6d 12 f2 ff       	call   0x4190c0
  4f7e53:	8b f0                	mov    esi,eax
  4f7e55:	2b 35 40 bd 72 0a    	sub    esi,DWORD PTR ds:0xa72bd40
  4f7e5b:	e9 2f 05 00 00       	jmp    0x4f838f
  4f7e60:	8b 0d c0 9b 5a 06    	mov    ecx,DWORD PTR ds:0x65a9bc0
  4f7e66:	85 c9                	test   ecx,ecx
  4f7e68:	0f 84 21 05 00 00    	je     0x4f838f
  4f7e6e:	80 7c 24 17 00       	cmp    BYTE PTR [esp+0x17],0x0
  4f7e73:	0f 84 16 05 00 00    	je     0x4f838f
  4f7e79:	8b 44 24 1c          	mov    eax,DWORD PTR [esp+0x1c]
  4f7e7d:	3d 18 fc ff ff       	cmp    eax,0xfffffc18
  4f7e82:	75 05                	jne    0x4f7e89
  4f7e84:	8d 41 ff             	lea    eax,[ecx-0x1]
  4f7e87:	eb a9                	jmp    0x4f7e32
  4f7e89:	85 c0                	test   eax,eax
  4f7e8b:	75 05                	jne    0x4f7e92
  4f7e8d:	8d 41 ff             	lea    eax,[ecx-0x1]
  4f7e90:	eb a0                	jmp    0x4f7e32
  4f7e92:	48                   	dec    eax
  4f7e93:	eb 9d                	jmp    0x4f7e32
  4f7e95:	33 ff                	xor    edi,edi
  4f7e97:	c7 05 3c bd 72 0a 00 	mov    DWORD PTR ds:0xa72bd3c,0x0
  4f7e9e:	00 00 00 
  4f7ea1:	33 c0                	xor    eax,eax
  4f7ea3:	c7 05 34 1c 6d 0a 00 	mov    DWORD PTR ds:0xa6d1c34,0x0
  4f7eaa:	00 00 00 
  4f7ead:	89 44 24 18          	mov    DWORD PTR [esp+0x18],eax
  4f7eb1:	c7 44 24 10 1b 00 00 	mov    DWORD PTR [esp+0x10],0x1b
  4f7eb8:	00 
  4f7eb9:	8d 47 1b             	lea    eax,[edi+0x1b]
  4f7ebc:	e9 d2 04 00 00       	jmp    0x4f8393
  4f7ec1:	b8 01 00 00 00       	mov    eax,0x1
  4f7ec6:	89 44 24 10          	mov    DWORD PTR [esp+0x10],eax
  4f7eca:	85 db                	test   ebx,ebx
  4f7ecc:	0f 85 c1 04 00 00    	jne    0x4f8393
  4f7ed2:	85 f6                	test   esi,esi
  4f7ed4:	0f 85 b9 04 00 00    	jne    0x4f8393
  4f7eda:	38 5c 24 2b          	cmp    BYTE PTR [esp+0x2b],bl
  4f7ede:	0f 85 af 04 00 00    	jne    0x4f8393
  4f7ee4:	33 c0                	xor    eax,eax
  4f7ee6:	89 44 24 10          	mov    DWORD PTR [esp+0x10],eax
  4f7eea:	e9 a4 04 00 00       	jmp    0x4f8393
  4f7eef:	c7 05 5c ba 5b 06 01 	mov    DWORD PTR ds:0x65bba5c,0x1
  4f7ef6:	00 00 00 
  4f7ef9:	e8 32 85 fd ff       	call   0x4d0430
  4f7efe:	f3 0f 10 05 d0 b5 5b 	movss  xmm0,DWORD PTR ds:0x65bb5d0
  4f7f05:	06 
  4f7f06:	f3 0f 59 05 44 d1 5d 	mulss  xmm0,DWORD PTR ds:0x5dd144
  4f7f0d:	00 
  4f7f0e:	8b 35 e8 4d 35 06    	mov    esi,DWORD PTR ds:0x6354de8
  4f7f14:	8b 3d b4 49 35 06    	mov    edi,DWORD PTR ds:0x63549b4
  4f7f1a:	51                   	push   ecx
  4f7f1b:	c7 05 5c ba 5b 06 00 	mov    DWORD PTR ds:0x65bba5c,0x0
  4f7f22:	00 00 00 
  4f7f25:	f3 0f 11 04 24       	movss  DWORD PTR [esp],xmm0
  4f7f2a:	ff 15 d8 c3 58 00    	call   DWORD PTR ds:0x58c3d8
  4f7f30:	f3 0f 10 05 cc b5 5b 	movss  xmm0,DWORD PTR ds:0x65bb5cc
  4f7f37:	06 
  4f7f38:	f3 0f 59 05 44 d1 5d 	mulss  xmm0,DWORD PTR ds:0x5dd144
  4f7f3f:	00 
  4f7f40:	d9 5c 24 24          	fstp   DWORD PTR [esp+0x24]
  4f7f44:	f3 0f 11 04 24       	movss  DWORD PTR [esp],xmm0
  4f7f49:	ff 15 d8 c3 58 00    	call   DWORD PTR ds:0x58c3d8
  4f7f4f:	d9 5c 24 28          	fstp   DWORD PTR [esp+0x28]
  4f7f53:	f3 0f 2c 44 24 28    	cvttss2si eax,DWORD PTR [esp+0x28]
  4f7f59:	51                   	push   ecx
  4f7f5a:	2b f0                	sub    esi,eax
  4f7f5c:	2b 35 c0 b5 5b 06    	sub    esi,DWORD PTR ds:0x65bb5c0
  4f7f62:	66 0f 6e c6          	movd   xmm0,esi
  4f7f66:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  4f7f69:	f3 0f 5e 05 cc b5 5b 	divss  xmm0,DWORD PTR ds:0x65bb5cc
  4f7f70:	06 
  4f7f71:	0f 5a c0             	cvtps2pd xmm0,xmm0
  4f7f74:	f2 0f 11 44 24 38    	movsd  QWORD PTR [esp+0x38],xmm0
  4f7f7a:	dd 44 24 38          	fld    QWORD PTR [esp+0x38]
  4f7f7e:	dd 1c 24             	fstp   QWORD PTR [esp]
  4f7f81:	e8 56 36 09 00       	call   0x58b5dc
  4f7f86:	f3 0f 2c 44 24 28    	cvttss2si eax,DWORD PTR [esp+0x28]
  4f7f8c:	dd 5c 24 38          	fstp   QWORD PTR [esp+0x38]
  4f7f90:	f2 0f 10 44 24 38    	movsd  xmm0,QWORD PTR [esp+0x38]
  4f7f96:	2b f8                	sub    edi,eax
  4f7f98:	2b 3d c4 b5 5b 06    	sub    edi,DWORD PTR ds:0x65bb5c4
  4f7f9e:	66 0f 5a c0          	cvtpd2ps xmm0,xmm0
  4f7fa2:	f3 0f 2c d8          	cvttss2si ebx,xmm0
  4f7fa6:	66 0f 6e c7          	movd   xmm0,edi
  4f7faa:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  4f7fad:	f3 0f 5e 05 d0 b5 5b 	divss  xmm0,DWORD PTR ds:0x65bb5d0
  4f7fb4:	06 
  4f7fb5:	0f 5a c0             	cvtps2pd xmm0,xmm0
  4f7fb8:	f2 0f 11 44 24 38    	movsd  QWORD PTR [esp+0x38],xmm0
  4f7fbe:	dd 44 24 38          	fld    QWORD PTR [esp+0x38]
  4f7fc2:	dd 1c 24             	fstp   QWORD PTR [esp]
  4f7fc5:	e8 12 36 09 00       	call   0x58b5dc
  4f7fca:	dd 5c 24 38          	fstp   QWORD PTR [esp+0x38]
  4f7fce:	f2 0f 10 44 24 38    	movsd  xmm0,QWORD PTR [esp+0x38]
  4f7fd4:	83 c4 08             	add    esp,0x8
  4f7fd7:	80 7c 24 15 00       	cmp    BYTE PTR [esp+0x15],0x0
  4f7fdc:	8b fb                	mov    edi,ebx
  4f7fde:	66 0f 5a c0          	cvtpd2ps xmm0,xmm0
  4f7fe2:	f3 0f 2c f0          	cvttss2si esi,xmm0
  4f7fe6:	89 74 24 18          	mov    DWORD PTR [esp+0x18],esi
  4f7fea:	0f 84 9f 03 00 00    	je     0x4f838f
  4f7ff0:	83 fb 01             	cmp    ebx,0x1
  4f7ff3:	7e 07                	jle    0x4f7ffc
  4f7ff5:	bb 01 00 00 00       	mov    ebx,0x1
  4f7ffa:	eb 0b                	jmp    0x4f8007
  4f7ffc:	83 fb ff             	cmp    ebx,0xffffffff
  4f7fff:	b8 ff ff ff ff       	mov    eax,0xffffffff
  4f8004:	0f 4c d8             	cmovl  ebx,eax
  4f8007:	83 fe 01             	cmp    esi,0x1
  4f800a:	7e 0a                	jle    0x4f8016
  4f800c:	be 01 00 00 00       	mov    esi,0x1
  4f8011:	e9 79 03 00 00       	jmp    0x4f838f
  4f8016:	8b 44 24 10          	mov    eax,DWORD PTR [esp+0x10]
  4f801a:	83 fe ff             	cmp    esi,0xffffffff
  4f801d:	0f 8d 70 03 00 00    	jge    0x4f8393
  4f8023:	83 ce ff             	or     esi,0xffffffff
  4f8026:	e9 68 03 00 00       	jmp    0x4f8393
  4f802b:	80 7c 24 15 00       	cmp    BYTE PTR [esp+0x15],0x0
  4f8030:	74 1c                	je     0x4f804e
  4f8032:	bf 1d 00 00 00       	mov    edi,0x1d
  4f8037:	83 cb ff             	or     ebx,0xffffffff
  4f803a:	b8 01 00 00 00       	mov    eax,0x1
  4f803f:	89 7c 24 18          	mov    DWORD PTR [esp+0x18],edi
  4f8043:	0b f3                	or     esi,ebx
  4f8045:	89 44 24 10          	mov    DWORD PTR [esp+0x10],eax
  4f8049:	e9 45 03 00 00       	jmp    0x4f8393
  4f804e:	ff 4c 24 18          	dec    DWORD PTR [esp+0x18]
  4f8052:	4f                   	dec    edi
  4f8053:	4b                   	dec    ebx
  4f8054:	4e                   	dec    esi
  4f8055:	e9 35 03 00 00       	jmp    0x4f838f
  4f805a:	2d 30 04 00 00       	sub    eax,0x430
  4f805f:	83 f8 1b             	cmp    eax,0x1b
  4f8062:	0f 87 27 03 00 00    	ja     0x4f838f
  4f8068:	0f b6 80 24 87 4f 00 	movzx  eax,BYTE PTR [eax+0x4f8724]
  4f806f:	ff 24 85 f4 86 4f 00 	jmp    DWORD PTR [eax*4+0x4f86f4]
  4f8076:	b9 7c d5 59 00       	mov    ecx,0x59d57c
  4f807b:	c7 05 d8 bc 5b 06 01 	mov    DWORD PTR ds:0x65bbcd8,0x1
  4f8082:	00 00 00 
  4f8085:	e8 d6 2f 01 00       	call   0x50b060
  4f808a:	6a 64                	push   0x64
  4f808c:	6a 00                	push   0x0
  4f808e:	68 20 2c 5e 00       	push   0x5e2c20
  4f8093:	e8 c8 2d 09 00       	call   0x58ae60
  4f8098:	f3 0f 10 05 c8 b5 5b 	movss  xmm0,DWORD PTR ds:0x65bb5c8
  4f809f:	06 
  4f80a0:	83 c4 0c             	add    esp,0xc
  4f80a3:	f3 0f 10 0d c0 d1 5d 	movss  xmm1,DWORD PTR ds:0x5dd1c0
  4f80aa:	00 
  4f80ab:	0f 2e c1             	ucomiss xmm0,xmm1
  4f80ae:	9f                   	lahf
  4f80af:	f6 c4 44             	test   ah,0x44
  4f80b2:	7a 0a                	jp     0x4f80be
  4f80b4:	f3 0f 10 15 44 d1 5d 	movss  xmm2,DWORD PTR ds:0x5dd144
  4f80bb:	00 
  4f80bc:	eb 03                	jmp    0x4f80c1
  4f80be:	0f 28 d1             	movaps xmm2,xmm1
  4f80c1:	f3 0f 11 15 c8 b5 5b 	movss  DWORD PTR ds:0x65bb5c8,xmm2
  4f80c8:	06 
  4f80c9:	e8 72 d6 ff ff       	call   0x4f5740
  4f80ce:	e8 9d 7e f9 ff       	call   0x48ff70
  4f80d3:	e8 98 7e f9 ff       	call   0x48ff70
  4f80d8:	e8 03 1b fa ff       	call   0x499be0
  4f80dd:	83 3d 9c 87 5e 00 00 	cmp    DWORD PTR ds:0x5e879c,0x0
  4f80e4:	0f 85 a5 02 00 00    	jne    0x4f838f
  4f80ea:	b9 7c d5 59 00       	mov    ecx,0x59d57c
  4f80ef:	c7 05 d8 bc 5b 06 00 	mov    DWORD PTR ds:0x65bbcd8,0x0
  4f80f6:	00 00 00 
  4f80f9:	e8 f2 2f 01 00       	call   0x50b0f0
  4f80fe:	e9 8c 02 00 00       	jmp    0x4f838f
  4f8103:	b9 7c d5 59 00       	mov    ecx,0x59d57c
  4f8108:	c7 05 d8 bc 5b 06 01 	mov    DWORD PTR ds:0x65bbcd8,0x1
  4f810f:	00 00 00 
  4f8112:	e8 49 2f 01 00       	call   0x50b060
  4f8117:	6a 64                	push   0x64
  4f8119:	6a 00                	push   0x0
  4f811b:	68 20 2c 5e 00       	push   0x5e2c20
  4f8120:	c7 44 24 2c 00 00 00 	mov    DWORD PTR [esp+0x2c],0x0
  4f8127:	00 
  4f8128:	e8 33 2d 09 00       	call   0x58ae60
  4f812d:	f3 0f 10 15 c8 b5 5b 	movss  xmm2,DWORD PTR ds:0x65bb5c8
  4f8134:	06 
  4f8135:	83 c4 0c             	add    esp,0xc
  4f8138:	f3 0f 5c 15 f8 d0 5d 	subss  xmm2,DWORD PTR ds:0x5dd0f8
  4f813f:	00 
  4f8140:	f3 0f 10 05 44 d1 5d 	movss  xmm0,DWORD PTR ds:0x5dd144
  4f8147:	00 
  4f8148:	0f 2f c2             	comiss xmm0,xmm2
  4f814b:	f3 0f 11 15 c8 b5 5b 	movss  DWORD PTR ds:0x65bb5c8,xmm2
  4f8152:	06 
  4f8153:	72 13                	jb     0x4f8168
  4f8155:	0f 28 d0             	movaps xmm2,xmm0
  4f8158:	c7 44 24 20 01 00 00 	mov    DWORD PTR [esp+0x20],0x1
  4f815f:	00 
  4f8160:	f3 0f 11 15 c8 b5 5b 	movss  DWORD PTR ds:0x65bb5c8,xmm2
  4f8167:	06 
  4f8168:	e8 d3 d5 ff ff       	call   0x4f5740
  4f816d:	e8 fe 7d f9 ff       	call   0x48ff70
  4f8172:	83 7c 24 20 00       	cmp    DWORD PTR [esp+0x20],0x0
  4f8177:	74 14                	je     0x4f818d
  4f8179:	ff 15 70 c2 58 00    	call   DWORD PTR ds:0x58c270
  4f817f:	68 03 04 00 00       	push   0x403
  4f8184:	ff 15 64 c2 58 00    	call   DWORD PTR ds:0x58c264
  4f818a:	83 c4 04             	add    esp,0x4
  4f818d:	e8 ee f4 ff ff       	call   0x4f7680
  4f8192:	e9 3c ff ff ff       	jmp    0x4f80d3
  4f8197:	b9 7c d5 59 00       	mov    ecx,0x59d57c
  4f819c:	c7 05 d8 bc 5b 06 01 	mov    DWORD PTR ds:0x65bbcd8,0x1
  4f81a3:	00 00 00 
  4f81a6:	e8 b5 2e 01 00       	call   0x50b060
  4f81ab:	6a 64                	push   0x64
  4f81ad:	6a 00                	push   0x0
  4f81af:	68 20 2c 5e 00       	push   0x5e2c20
  4f81b4:	c7 44 24 2c 00 00 00 	mov    DWORD PTR [esp+0x2c],0x0
  4f81bb:	00 
  4f81bc:	e8 9f 2c 09 00       	call   0x58ae60
  4f81c1:	f3 0f 10 15 c8 b5 5b 	movss  xmm2,DWORD PTR ds:0x65bb5c8
  4f81c8:	06 
  4f81c9:	83 c4 0c             	add    esp,0xc
  4f81cc:	0f 2e 15 44 d1 5d 00 	ucomiss xmm2,DWORD PTR ds:0x5dd144
  4f81d3:	9f                   	lahf
  4f81d4:	f6 c4 44             	test   ah,0x44
  4f81d7:	7a 0a                	jp     0x4f81e3
  4f81d9:	f3 0f 10 15 68 d1 5d 	movss  xmm2,DWORD PTR ds:0x5dd168
  4f81e0:	00 
  4f81e1:	eb 28                	jmp    0x4f820b
  4f81e3:	f3 0f 58 15 f8 d0 5d 	addss  xmm2,DWORD PTR ds:0x5dd0f8
  4f81ea:	00 
  4f81eb:	f3 0f 10 05 c0 d1 5d 	movss  xmm0,DWORD PTR ds:0x5dd1c0
  4f81f2:	00 
  4f81f3:	0f 2f d0             	comiss xmm2,xmm0
  4f81f6:	f3 0f 11 15 c8 b5 5b 	movss  DWORD PTR ds:0x65bb5c8,xmm2
  4f81fd:	06 
  4f81fe:	72 13                	jb     0x4f8213
  4f8200:	0f 28 d0             	movaps xmm2,xmm0
  4f8203:	c7 44 24 20 01 00 00 	mov    DWORD PTR [esp+0x20],0x1
  4f820a:	00 
  4f820b:	f3 0f 11 15 c8 b5 5b 	movss  DWORD PTR ds:0x65bb5c8,xmm2
  4f8212:	06 
  4f8213:	e8 28 d5 ff ff       	call   0x4f5740
  4f8218:	e8 53 7d f9 ff       	call   0x48ff70
  4f821d:	83 7c 24 20 00       	cmp    DWORD PTR [esp+0x20],0x0
  4f8222:	74 14                	je     0x4f8238
  4f8224:	ff 15 70 c2 58 00    	call   DWORD PTR ds:0x58c270
  4f822a:	68 03 04 00 00       	push   0x403
  4f822f:	ff 15 64 c2 58 00    	call   DWORD PTR ds:0x58c264
  4f8235:	83 c4 04             	add    esp,0x4
  4f8238:	e8 43 f4 ff ff       	call   0x4f7680
  4f823d:	e9 91 fe ff ff       	jmp    0x4f80d3
  4f8242:	80 7c 24 15 00       	cmp    BYTE PTR [esp+0x15],0x0
  4f8247:	74 20                	je     0x4f8269
  4f8249:	bf 1e 00 00 00       	mov    edi,0x1e
  4f824e:	c7 44 24 18 1d 00 00 	mov    DWORD PTR [esp+0x18],0x1d
  4f8255:	00 
  4f8256:	c7 44 24 10 01 00 00 	mov    DWORD PTR [esp+0x10],0x1
  4f825d:	00 
  4f825e:	83 ce ff             	or     esi,0xffffffff
  4f8261:	8d 47 e3             	lea    eax,[edi-0x1d]
  4f8264:	e9 2a 01 00 00       	jmp    0x4f8393
  4f8269:	ff 4c 24 18          	dec    DWORD PTR [esp+0x18]
  4f826d:	4e                   	dec    esi
  4f826e:	e9 1c 01 00 00       	jmp    0x4f838f
  4f8273:	80 7c 24 15 00       	cmp    BYTE PTR [esp+0x15],0x0
  4f8278:	0f 84 0c 01 00 00    	je     0x4f838a
  4f827e:	be 01 00 00 00       	mov    esi,0x1
  4f8283:	c7 44 24 18 1f 00 00 	mov    DWORD PTR [esp+0x18],0x1f
  4f828a:	00 
  4f828b:	8b c6                	mov    eax,esi
  4f828d:	bf 1e 00 00 00       	mov    edi,0x1e
  4f8292:	89 44 24 10          	mov    DWORD PTR [esp+0x10],eax
  4f8296:	e9 f8 00 00 00       	jmp    0x4f8393
  4f829b:	80 7c 24 15 00       	cmp    BYTE PTR [esp+0x15],0x0
  4f82a0:	74 1e                	je     0x4f82c0
  4f82a2:	b8 01 00 00 00       	mov    eax,0x1
  4f82a7:	c7 44 24 18 1e 00 00 	mov    DWORD PTR [esp+0x18],0x1e
  4f82ae:	00 
  4f82af:	bf 1d 00 00 00       	mov    edi,0x1d
  4f82b4:	89 44 24 10          	mov    DWORD PTR [esp+0x10],eax
  4f82b8:	83 cb ff             	or     ebx,0xffffffff
  4f82bb:	e9 d3 00 00 00       	jmp    0x4f8393
  4f82c0:	4f                   	dec    edi
  4f82c1:	4b                   	dec    ebx
  4f82c2:	e9 c8 00 00 00       	jmp    0x4f838f
  4f82c7:	80 7c 24 15 00       	cmp    BYTE PTR [esp+0x15],0x0
  4f82cc:	74 1d                	je     0x4f82eb
  4f82ce:	bb 01 00 00 00       	mov    ebx,0x1
  4f82d3:	c7 44 24 18 1e 00 00 	mov    DWORD PTR [esp+0x18],0x1e
  4f82da:	00 
  4f82db:	8b c3                	mov    eax,ebx
  4f82dd:	bf 1f 00 00 00       	mov    edi,0x1f
  4f82e2:	89 44 24 10          	mov    DWORD PTR [esp+0x10],eax
  4f82e6:	e9 a8 00 00 00       	jmp    0x4f8393
  4f82eb:	47                   	inc    edi
  4f82ec:	43                   	inc    ebx
  4f82ed:	e9 9d 00 00 00       	jmp    0x4f838f
  4f82f2:	80 7c 24 15 00       	cmp    BYTE PTR [esp+0x15],0x0
  4f82f7:	74 1d                	je     0x4f8316
  4f82f9:	be 01 00 00 00       	mov    esi,0x1
  4f82fe:	c7 44 24 18 1f 00 00 	mov    DWORD PTR [esp+0x18],0x1f
  4f8305:	00 
  4f8306:	8b c6                	mov    eax,esi
  4f8308:	bf 1d 00 00 00       	mov    edi,0x1d
  4f830d:	83 cb ff             	or     ebx,0xffffffff
  4f8310:	89 44 24 10          	mov    DWORD PTR [esp+0x10],eax
  4f8314:	eb 7d                	jmp    0x4f8393
  4f8316:	4f                   	dec    edi
  4f8317:	4b                   	dec    ebx
  4f8318:	eb 70                	jmp    0x4f838a
  4f831a:	80 7c 24 15 00       	cmp    BYTE PTR [esp+0x15],0x0
  4f831f:	74 1d                	je     0x4f833e
  4f8321:	bb 01 00 00 00       	mov    ebx,0x1
  4f8326:	c7 44 24 18 1d 00 00 	mov    DWORD PTR [esp+0x18],0x1d
  4f832d:	00 
  4f832e:	8b c3                	mov    eax,ebx
  4f8330:	bf 1f 00 00 00       	mov    edi,0x1f
  4f8335:	83 ce ff             	or     esi,0xffffffff
  4f8338:	89 44 24 10          	mov    DWORD PTR [esp+0x10],eax
  4f833c:	eb 55                	jmp    0x4f8393
  4f833e:	ff 4c 24 18          	dec    DWORD PTR [esp+0x18]
  4f8342:	47                   	inc    edi
  4f8343:	43                   	inc    ebx
  4f8344:	4e                   	dec    esi
  4f8345:	eb 48                	jmp    0x4f838f
  4f8347:	8a 44 24 16          	mov    al,BYTE PTR [esp+0x16]
  4f834b:	24 12                	and    al,0x12
  4f834d:	3c 12                	cmp    al,0x12
  4f834f:	75 3e                	jne    0x4f838f
  4f8351:	bf 1e 00 00 00       	mov    edi,0x1e
  4f8356:	b8 01 00 00 00       	mov    eax,0x1
  4f835b:	33 db                	xor    ebx,ebx
  4f835d:	89 7c 24 18          	mov    DWORD PTR [esp+0x18],edi
  4f8361:	33 f6                	xor    esi,esi
  4f8363:	89 44 24 10          	mov    DWORD PTR [esp+0x10],eax
  4f8367:	eb 2a                	jmp    0x4f8393
  4f8369:	80 7c 24 15 00       	cmp    BYTE PTR [esp+0x15],0x0
  4f836e:	74 18                	je     0x4f8388
  4f8370:	bb 01 00 00 00       	mov    ebx,0x1
  4f8375:	bf 1f 00 00 00       	mov    edi,0x1f
  4f837a:	8b c3                	mov    eax,ebx
  4f837c:	89 7c 24 18          	mov    DWORD PTR [esp+0x18],edi
  4f8380:	8b f3                	mov    esi,ebx
  4f8382:	89 44 24 10          	mov    DWORD PTR [esp+0x10],eax
  4f8386:	eb 0b                	jmp    0x4f8393
  4f8388:	47                   	inc    edi
  4f8389:	43                   	inc    ebx
  4f838a:	ff 44 24 18          	inc    DWORD PTR [esp+0x18]
  4f838e:	46                   	inc    esi
  4f838f:	8b 44 24 10          	mov    eax,DWORD PTR [esp+0x10]
  4f8393:	8b 0d 9c 1c 6d 0a    	mov    ecx,DWORD PTR ds:0xa6d1c9c
  4f8399:	89 4c 24 24          	mov    DWORD PTR [esp+0x24],ecx
  4f839d:	03 cb                	add    ecx,ebx
  4f839f:	89 4c 24 2c          	mov    DWORD PTR [esp+0x2c],ecx
  4f83a3:	8b 0d 40 bd 72 0a    	mov    ecx,DWORD PTR ds:0xa72bd40
  4f83a9:	89 4c 24 30          	mov    DWORD PTR [esp+0x30],ecx
  4f83ad:	8d 14 31             	lea    edx,[ecx+esi*1]
  4f83b0:	89 54 24 20          	mov    DWORD PTR [esp+0x20],edx
  4f83b4:	83 f8 01             	cmp    eax,0x1
  4f83b7:	0f 85 f7 00 00 00    	jne    0x4f84b4
  4f83bd:	8b 7c 24 20          	mov    edi,DWORD PTR [esp+0x20]
  4f83c1:	33 d2                	xor    edx,edx
  4f83c3:	3b f8                	cmp    edi,eax
  4f83c5:	0f 9c c2             	setl   dl
  4f83c8:	33 c9                	xor    ecx,ecx
  4f83ca:	39 44 24 2c          	cmp    DWORD PTR [esp+0x2c],eax
  4f83ce:	0f 9c c1             	setl   cl
  4f83d1:	0b d1                	or     edx,ecx
  4f83d3:	75 4f                	jne    0x4f8424
  4f83d5:	8b 44 24 24          	mov    eax,DWORD PTR [esp+0x24]
  4f83d9:	8b 4c 24 2c          	mov    ecx,DWORD PTR [esp+0x2c]
  4f83dd:	2b c1                	sub    eax,ecx
  4f83df:	99                   	cdq
  4f83e0:	33 c2                	xor    eax,edx
  4f83e2:	2b c2                	sub    eax,edx
  4f83e4:	3b 05 d4 b5 5b 06    	cmp    eax,DWORD PTR ds:0x65bb5d4
  4f83ea:	7f 38                	jg     0x4f8424
  4f83ec:	8b 44 24 30          	mov    eax,DWORD PTR [esp+0x30]
  4f83f0:	2b c7                	sub    eax,edi
  4f83f2:	99                   	cdq
  4f83f3:	33 c2                	xor    eax,edx
  4f83f5:	2b c2                	sub    eax,edx
  4f83f7:	3b 05 d8 b5 5b 06    	cmp    eax,DWORD PTR ds:0x65bb5d8
  4f83fd:	7f 25                	jg     0x4f8424
  4f83ff:	81 f9 ff 0b 00 00    	cmp    ecx,0xbff
  4f8405:	77 1d                	ja     0x4f8424
  4f8407:	81 ff ff 07 00 00    	cmp    edi,0x7ff
  4f840d:	77 15                	ja     0x4f8424
  4f840f:	69 c7 01 0c 00 00    	imul   eax,edi,0xc01
  4f8415:	8a 84 08 58 54 78 02 	mov    al,BYTE PTR [eax+ecx*1+0x2785458]
  4f841c:	3c 3a                	cmp    al,0x3a
  4f841e:	0f 85 24 01 00 00    	jne    0x4f8548
  4f8424:	f6 44 24 16 04       	test   BYTE PTR [esp+0x16],0x4
  4f8429:	0f 85 19 01 00 00    	jne    0x4f8548
  4f842f:	33 c0                	xor    eax,eax
  4f8431:	c7 05 bc 8c 5a 06 01 	mov    DWORD PTR ds:0x65a8cbc,0x1
  4f8438:	00 00 00 
  4f843b:	b9 7c d5 59 00       	mov    ecx,0x59d57c
  4f8440:	89 44 24 18          	mov    DWORD PTR [esp+0x18],eax
  4f8444:	33 ff                	xor    edi,edi
  4f8446:	c7 05 58 f9 59 06 01 	mov    DWORD PTR ds:0x659f958,0x1
  4f844d:	00 00 00 
  4f8450:	c7 05 d8 bc 5b 06 01 	mov    DWORD PTR ds:0x65bbcd8,0x1
  4f8457:	00 00 00 
  4f845a:	e8 01 2c 01 00       	call   0x50b060
  4f845f:	b9 ac a0 5a 00       	mov    ecx,0x5aa0ac
  4f8464:	e8 a7 e0 ff ff       	call   0x4f6510
  4f8469:	39 3d 9c 87 5e 00    	cmp    DWORD PTR ds:0x5e879c,edi
  4f846f:	75 10                	jne    0x4f8481
  4f8471:	b9 7c d5 59 00       	mov    ecx,0x59d57c
  4f8476:	89 3d d8 bc 5b 06    	mov    DWORD PTR ds:0x65bbcd8,edi
  4f847c:	e8 6f 2c 01 00       	call   0x50b0f0
  4f8481:	8a 44 24 16          	mov    al,BYTE PTR [esp+0x16]
  4f8485:	24 06                	and    al,0x6
  4f8487:	89 3d 58 f9 59 06    	mov    DWORD PTR ds:0x659f958,edi
  4f848d:	89 3d bc 8c 5a 06    	mov    DWORD PTR ds:0x65a8cbc,edi
  4f8493:	89 3d 3c bd 72 0a    	mov    DWORD PTR ds:0xa72bd3c,edi
  4f8499:	89 3d 34 1c 6d 0a    	mov    DWORD PTR ds:0xa6d1c34,edi
  4f849f:	3c 02                	cmp    al,0x2
  4f84a1:	75 08                	jne    0x4f84ab
  4f84a3:	8b 5c 24 3c          	mov    ebx,DWORD PTR [esp+0x3c]
  4f84a7:	8b 74 24 38          	mov    esi,DWORD PTR [esp+0x38]
  4f84ab:	89 7c 24 10          	mov    DWORD PTR [esp+0x10],edi
  4f84af:	e9 25 f8 ff ff       	jmp    0x4f7cd9
  4f84b4:	33 c9                	xor    ecx,ecx
  4f84b6:	83 fa 01             	cmp    edx,0x1
  4f84b9:	8b 54 24 2c          	mov    edx,DWORD PTR [esp+0x2c]
  4f84bd:	0f 9c c1             	setl   cl
  4f84c0:	33 c0                	xor    eax,eax
  4f84c2:	83 fa 01             	cmp    edx,0x1
  4f84c5:	0f 9c c0             	setl   al
  4f84c8:	0b c8                	or     ecx,eax
  4f84ca:	a1 d4 b5 5b 06       	mov    eax,ds:0x65bb5d4
  4f84cf:	8b 0d d8 b5 5b 06    	mov    ecx,DWORD PTR ds:0x65bb5d8
  4f84d5:	89 44 24 24          	mov    DWORD PTR [esp+0x24],eax
  4f84d9:	75 4c                	jne    0x4f8527
  4f84db:	a1 9c 1c 6d 0a       	mov    eax,ds:0xa6d1c9c
  4f84e0:	2b c2                	sub    eax,edx
  4f84e2:	99                   	cdq
  4f84e3:	33 c2                	xor    eax,edx
  4f84e5:	2b c2                	sub    eax,edx
  4f84e7:	3b 44 24 24          	cmp    eax,DWORD PTR [esp+0x24]
  4f84eb:	7f 3a                	jg     0x4f8527
  4f84ed:	a1 40 bd 72 0a       	mov    eax,ds:0xa72bd40
  4f84f2:	2b 44 24 20          	sub    eax,DWORD PTR [esp+0x20]
  4f84f6:	99                   	cdq
  4f84f7:	33 c2                	xor    eax,edx
  4f84f9:	2b c2                	sub    eax,edx
  4f84fb:	3b c1                	cmp    eax,ecx
  4f84fd:	7f 28                	jg     0x4f8527
  4f84ff:	8b 54 24 2c          	mov    edx,DWORD PTR [esp+0x2c]
  4f8503:	81 fa ff 0b 00 00    	cmp    edx,0xbff
  4f8509:	77 1c                	ja     0x4f8527
  4f850b:	8b 44 24 20          	mov    eax,DWORD PTR [esp+0x20]
  4f850f:	3d ff 07 00 00       	cmp    eax,0x7ff
  4f8514:	77 11                	ja     0x4f8527
  4f8516:	69 c0 01 0c 00 00    	imul   eax,eax,0xc01
  4f851c:	8a 84 10 58 54 78 02 	mov    al,BYTE PTR [eax+edx*1+0x2785458]
  4f8523:	3c 3a                	cmp    al,0x3a
  4f8525:	75 12                	jne    0x4f8539
  4f8527:	8a 44 24 16          	mov    al,BYTE PTR [esp+0x16]
  4f852b:	24 06                	and    al,0x6
  4f852d:	3c 02                	cmp    al,0x2
  4f852f:	75 08                	jne    0x4f8539
  4f8531:	8b 5c 24 3c          	mov    ebx,DWORD PTR [esp+0x3c]
  4f8535:	8b 74 24 38          	mov    esi,DWORD PTR [esp+0x38]
  4f8539:	83 7c 24 10 00       	cmp    DWORD PTR [esp+0x10],0x0
  4f853e:	8b 44 24 24          	mov    eax,DWORD PTR [esp+0x24]
  4f8542:	0f 84 a8 f7 ff ff    	je     0x4f7cf0
  4f8548:	b9 70 43 59 00       	mov    ecx,0x594370
  4f854d:	e8 3e 41 01 00       	call   0x50c690
  4f8552:	b9 70 43 59 00       	mov    ecx,0x594370
  4f8557:	e8 64 3f 01 00       	call   0x50c4c0
  4f855c:	b9 7c d5 59 00       	mov    ecx,0x59d57c
  4f8561:	c7 05 d8 bc 5b 06 01 	mov    DWORD PTR ds:0x65bbcd8,0x1
  4f8568:	00 00 00 
  4f856b:	e8 f0 2a 01 00       	call   0x50b060
  4f8570:	83 3d 5c ba 5b 06 00 	cmp    DWORD PTR ds:0x65bba5c,0x0
  4f8577:	8b 3d 50 ba 5b 06    	mov    edi,DWORD PTR ds:0x65bba50
  4f857d:	75 29                	jne    0x4f85a8
  4f857f:	c7 05 d8 bc 5b 06 01 	mov    DWORD PTR ds:0x65bbcd8,0x1
  4f8586:	00 00 00 
  4f8589:	c7 05 50 ba 5b 06 01 	mov    DWORD PTR ds:0x65bba50,0x1
  4f8590:	00 00 00 
  4f8593:	e8 88 31 01 00       	call   0x50b720
  4f8598:	c7 05 d8 bc 5b 06 01 	mov    DWORD PTR ds:0x65bbcd8,0x1
  4f859f:	00 00 00 
  4f85a2:	89 3d 50 ba 5b 06    	mov    DWORD PTR ds:0x65bba50,edi
  4f85a8:	83 7c 24 10 1b       	cmp    DWORD PTR [esp+0x10],0x1b
  4f85ad:	c6 05 c9 e3 17 02 00 	mov    BYTE PTR ds:0x217e3c9,0x0
  4f85b4:	c7 05 54 54 78 02 00 	mov    DWORD PTR ds:0x2785454,0x0
  4f85bb:	00 00 00 
  4f85be:	c7 05 94 68 d8 02 00 	mov    DWORD PTR ds:0x2d86894,0x0
  4f85c5:	00 00 00 
  4f85c8:	75 17                	jne    0x4f85e1
  4f85ca:	32 c0                	xor    al,al
  4f85cc:	5f                   	pop    edi
  4f85cd:	5e                   	pop    esi
  4f85ce:	5b                   	pop    ebx
  4f85cf:	8b 8c 24 b0 00 00 00 	mov    ecx,DWORD PTR [esp+0xb0]
  4f85d6:	33 cc                	xor    ecx,esp
  4f85d8:	e8 d1 1a 09 00       	call   0x58a0ae
  4f85dd:	8b e5                	mov    esp,ebp
  4f85df:	5d                   	pop    ebp
  4f85e0:	c3                   	ret
  4f85e1:	8b 3d 9c 1c 6d 0a    	mov    edi,DWORD PTR ds:0xa6d1c9c
  4f85e7:	a1 40 bd 72 0a       	mov    eax,ds:0xa72bd40
  4f85ec:	03 fb                	add    edi,ebx
  4f85ee:	03 c6                	add    eax,esi
  4f85f0:	89 3d 3c bd 72 0a    	mov    DWORD PTR ds:0xa72bd3c,edi
  4f85f6:	8b d0                	mov    edx,eax
  4f85f8:	a3 34 1c 6d 0a       	mov    ds:0xa6d1c34,eax
  4f85fd:	8b cf                	mov    ecx,edi
  4f85ff:	89 1d c0 8c 5a 06    	mov    DWORD PTR ds:0x65a8cc0,ebx
  4f8605:	89 35 90 96 5a 06    	mov    DWORD PTR ds:0x65a9690,esi
  4f860b:	e8 10 0b f2 ff       	call   0x419120
  4f8610:	85 c0                	test   eax,eax
  4f8612:	78 14                	js     0x4f8628
  4f8614:	8b 0d c0 6e 5e 00    	mov    ecx,DWORD PTR ds:0x5e6ec0
  4f861a:	80 7c 24 17 00       	cmp    BYTE PTR [esp+0x17],0x0
  4f861f:	0f 45 c8             	cmovne ecx,eax
  4f8622:	89 0d c0 6e 5e 00    	mov    DWORD PTR ds:0x5e6ec0,ecx
  4f8628:	81 ff ff 0b 00 00    	cmp    edi,0xbff
  4f862e:	77 2e                	ja     0x4f865e
  4f8630:	a1 34 1c 6d 0a       	mov    eax,ds:0xa6d1c34
  4f8635:	3d ff 07 00 00       	cmp    eax,0x7ff
  4f863a:	77 22                	ja     0x4f865e
  4f863c:	69 c0 01 0c 00 00    	imul   eax,eax,0xc01
  4f8642:	8a 84 38 48 94 cf 00 	mov    al,BYTE PTR [eax+edi*1+0xcf9448]
  4f8649:	5f                   	pop    edi
  4f864a:	5e                   	pop    esi
  4f864b:	5b                   	pop    ebx
  4f864c:	8b 8c 24 b0 00 00 00 	mov    ecx,DWORD PTR [esp+0xb0]
  4f8653:	33 cc                	xor    ecx,esp
  4f8655:	e8 54 1a 09 00       	call   0x58a0ae
  4f865a:	8b e5                	mov    esp,ebp
  4f865c:	5d                   	pop    ebp
  4f865d:	c3                   	ret
  4f865e:	8b 8c 24 bc 00 00 00 	mov    ecx,DWORD PTR [esp+0xbc]
  4f8665:	b0 20                	mov    al,0x20
  4f8667:	5f                   	pop    edi
  4f8668:	5e                   	pop    esi
  4f8669:	5b                   	pop    ebx
  4f866a:	33 cc                	xor    ecx,esp
  4f866c:	e8 3d 1a 09 00       	call   0x58a0ae
  4f8671:	8b e5                	mov    esp,ebp
  4f8673:	5d                   	pop    ebp
  4f8674:	c3                   	ret
