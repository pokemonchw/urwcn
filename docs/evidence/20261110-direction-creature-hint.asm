
/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe:     file format pei-i386


Disassembly of section .text:

00514a20 <.text+0x113a20>:
  514a20:	55                   	push   ebp
  514a21:	8b ec                	mov    ebp,esp
  514a23:	81 ec 30 0c 00 00    	sub    esp,0xc30
  514a29:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  514a2e:	33 c5                	xor    eax,ebp
  514a30:	89 45 f8             	mov    DWORD PTR [ebp-0x8],eax
  514a33:	53                   	push   ebx
  514a34:	56                   	push   esi
  514a35:	bb 01 02 00 00       	mov    ebx,0x201
  514a3a:	33 c9                	xor    ecx,ecx
  514a3c:	57                   	push   edi
  514a3d:	89 9d d0 f3 ff ff    	mov    DWORD PTR [ebp-0xc30],ebx
  514a43:	0f 1f 40 00          	nop    DWORD PTR [eax+0x0]
  514a47:	66 0f 1f 84 00 00 00 	nop    WORD PTR [eax+eax*1+0x0]
  514a4e:	00 00 
  514a50:	8a 81 90 9f 5a 00    	mov    al,BYTE PTR [ecx+0x5a9f90]
  514a56:	8d 49 01             	lea    ecx,[ecx+0x1]
  514a59:	88 84 0d f3 f3 ff ff 	mov    BYTE PTR [ebp+ecx*1-0xc0d],al
  514a60:	84 c0                	test   al,al
  514a62:	75 ec                	jne    0x514a50
  514a64:	ba 50 c9 5a 00       	mov    edx,0x5ac950
  514a69:	8d 8d f4 f3 ff ff    	lea    ecx,[ebp-0xc0c]
  514a6f:	e8 bc f9 fb ff       	call   0x4d4430
  514a74:	8b 3d 50 c3 58 00    	mov    edi,DWORD PTR ds:0x58c350
  514a7a:	a1 b0 4b 35 06       	mov    eax,ds:0x6354bb0
  514a7f:	83 ce ff             	or     esi,0xffffffff
  514a82:	8b 0d ec c4 58 00    	mov    ecx,DWORD PTR ds:0x58c4ec
  514a88:	3b c6                	cmp    eax,esi
  514a8a:	0f 84 7f 02 00 00    	je     0x514d0f
  514a90:	68 c4 4d 35 06       	push   0x6354dc4
  514a95:	85 c0                	test   eax,eax
  514a97:	75 07                	jne    0x514aa0
  514a99:	68 10 eb 34 06       	push   0x634eb10
  514a9e:	eb 02                	jmp    0x514aa2
  514aa0:	6a 00                	push   0x0
  514aa2:	ff d1                	call   ecx
  514aa4:	8b 0d b0 4b 35 06    	mov    ecx,DWORD PTR ds:0x6354bb0
  514aaa:	83 c4 08             	add    esp,0x8
  514aad:	41                   	inc    ecx
  514aae:	a3 bc 4d 35 06       	mov    ds:0x6354dbc,eax
  514ab3:	85 c0                	test   eax,eax
  514ab5:	0f 44 ce             	cmove  ecx,esi
  514ab8:	89 0d b0 4b 35 06    	mov    DWORD PTR ds:0x6354bb0,ecx
  514abe:	0f 84 4b 02 00 00    	je     0x514d0f
  514ac4:	8d 95 f4 fb ff ff    	lea    edx,[ebp-0x40c]
  514aca:	2b d0                	sub    edx,eax
  514acc:	0f 1f 40 00          	nop    DWORD PTR [eax+0x0]
  514ad0:	8a 08                	mov    cl,BYTE PTR [eax]
  514ad2:	8d 40 01             	lea    eax,[eax+0x1]
  514ad5:	88 4c 02 ff          	mov    BYTE PTR [edx+eax*1-0x1],cl
  514ad9:	84 c9                	test   cl,cl
  514adb:	75 f3                	jne    0x514ad0
  514add:	8d 85 f4 fb ff ff    	lea    eax,[ebp-0x40c]
  514ae3:	33 f6                	xor    esi,esi
  514ae5:	50                   	push   eax
  514ae6:	8d 85 f4 f7 ff ff    	lea    eax,[ebp-0x80c]
  514aec:	68 04 9f 5a 00       	push   0x5a9f04
  514af1:	50                   	push   eax
  514af2:	e8 d9 c5 ee ff       	call   0x4010d0
  514af7:	83 c4 0c             	add    esp,0xc
  514afa:	8d 85 f4 f7 ff ff    	lea    eax,[ebp-0x80c]
  514b00:	50                   	push   eax
  514b01:	8d 85 f4 f3 ff ff    	lea    eax,[ebp-0xc0c]
  514b07:	50                   	push   eax
  514b08:	ff d7                	call   edi
  514b0a:	85 c0                	test   eax,eax
  514b0c:	b8 01 00 00 00       	mov    eax,0x1
  514b11:	0f 45 f0             	cmovne esi,eax
  514b14:	8d 85 f4 fb ff ff    	lea    eax,[ebp-0x40c]
  514b1a:	50                   	push   eax
  514b1b:	8d 85 f4 f7 ff ff    	lea    eax,[ebp-0x80c]
  514b21:	68 58 c9 5a 00       	push   0x5ac958
  514b26:	50                   	push   eax
  514b27:	e8 a4 c5 ee ff       	call   0x4010d0
  514b2c:	83 c4 14             	add    esp,0x14
  514b2f:	8d 85 f4 f7 ff ff    	lea    eax,[ebp-0x80c]
  514b35:	50                   	push   eax
  514b36:	8d 85 f4 f3 ff ff    	lea    eax,[ebp-0xc0c]
  514b3c:	50                   	push   eax
  514b3d:	ff d7                	call   edi
  514b3f:	83 c4 08             	add    esp,0x8
  514b42:	85 c0                	test   eax,eax
  514b44:	75 4c                	jne    0x514b92
  514b46:	85 f6                	test   esi,esi
  514b48:	75 48                	jne    0x514b92
  514b4a:	ff 35 54 ba 5b 06    	push   DWORD PTR ds:0x65bba54
  514b50:	8d 85 f4 fb ff ff    	lea    eax,[ebp-0x40c]
  514b56:	ba 40 01 00 00       	mov    edx,0x140
  514b5b:	ff 35 c4 ba 5b 06    	push   DWORD PTR ds:0x65bbac4
  514b61:	8b cb                	mov    ecx,ebx
  514b63:	50                   	push   eax
  514b64:	e8 37 9a ff ff       	call   0x50e5a0
  514b69:	8d 8d f4 fb ff ff    	lea    ecx,[ebp-0x40c]
  514b6f:	83 c4 0c             	add    esp,0xc
  514b72:	8d 51 01             	lea    edx,[ecx+0x1]
  514b75:	8a 01                	mov    al,BYTE PTR [ecx]
  514b77:	41                   	inc    ecx
  514b78:	84 c0                	test   al,al
  514b7a:	75 f9                	jne    0x514b75
  514b7c:	2b ca                	sub    ecx,edx
  514b7e:	8d 1c cb             	lea    ebx,[ebx+ecx*8]
  514b81:	89 9d d0 f3 ff ff    	mov    DWORD PTR [ebp-0xc30],ebx
  514b87:	89 1d b4 1c 5c 0a    	mov    DWORD PTR ds:0xa5c1cb4,ebx
  514b8d:	e9 e8 fe ff ff       	jmp    0x514a7a
  514b92:	8d bd f4 fb ff ff    	lea    edi,[ebp-0x40c]
  514b98:	8d 4f 01             	lea    ecx,[edi+0x1]
  514b9b:	0f 1f 44 00 00       	nop    DWORD PTR [eax+eax*1+0x0]
  514ba0:	8a 07                	mov    al,BYTE PTR [edi]
  514ba2:	47                   	inc    edi
  514ba3:	84 c0                	test   al,al
  514ba5:	75 f9                	jne    0x514ba0
  514ba7:	0f 28 05 d0 d8 5d 00 	movaps xmm0,XMMWORD PTR ds:0x5dd8d0
  514bae:	8d 85 e4 f3 ff ff    	lea    eax,[ebp-0xc1c]
  514bb4:	50                   	push   eax
  514bb5:	ff 35 10 bb 5b 06    	push   DWORD PTR ds:0x65bbb10
  514bbb:	8d 85 d4 f3 ff ff    	lea    eax,[ebp-0xc2c]
  514bc1:	89 9d e4 f3 ff ff    	mov    DWORD PTR [ebp-0xc1c],ebx
  514bc7:	50                   	push   eax
  514bc8:	ff 35 28 20 5c 0a    	push   DWORD PTR ds:0xa5c2028
  514bce:	2b f9                	sub    edi,ecx
  514bd0:	c7 85 e8 f3 ff ff 3b 	mov    DWORD PTR [ebp-0xc18],0x13b
  514bd7:	01 00 00 
  514bda:	0f 11 85 d4 f3 ff ff 	movups XMMWORD PTR [ebp-0xc2c],xmm0
  514be1:	c7 85 ec f3 ff ff 07 	mov    DWORD PTR [ebp-0xc14],0x7
  514be8:	00 00 00 
  514beb:	c7 85 f0 f3 ff ff 20 	mov    DWORD PTR [ebp-0xc10],0x20
  514bf2:	00 00 00 
  514bf5:	ff 15 04 c2 58 00    	call   DWORD PTR ds:0x58c204
  514bfb:	83 c4 10             	add    esp,0x10
  514bfe:	85 ff                	test   edi,edi
  514c00:	7e 71                	jle    0x514c73
  514c02:	8d 73 07             	lea    esi,[ebx+0x7]
  514c05:	8b df                	mov    ebx,edi
  514c07:	66 0f 1f 84 00 00 00 	nop    WORD PTR [eax+eax*1+0x0]
  514c0e:	00 00 
  514c10:	0f 28 05 f0 d8 5d 00 	movaps xmm0,XMMWORD PTR ds:0x5dd8f0
  514c17:	8d 85 e4 f3 ff ff    	lea    eax,[ebp-0xc1c]
  514c1d:	50                   	push   eax
  514c1e:	ff 35 10 bb 5b 06    	push   DWORD PTR ds:0x65bbb10
  514c24:	8d 85 d4 f3 ff ff    	lea    eax,[ebp-0xc2c]
  514c2a:	89 b5 e4 f3 ff ff    	mov    DWORD PTR [ebp-0xc1c],esi
  514c30:	50                   	push   eax
  514c31:	ff 35 28 20 5c 0a    	push   DWORD PTR ds:0xa5c2028
  514c37:	0f 11 85 d4 f3 ff ff 	movups XMMWORD PTR [ebp-0xc2c],xmm0
  514c3e:	c7 85 e8 f3 ff ff 3b 	mov    DWORD PTR [ebp-0xc18],0x13b
  514c45:	01 00 00 
  514c48:	c7 85 ec f3 ff ff 08 	mov    DWORD PTR [ebp-0xc14],0x8
  514c4f:	00 00 00 
  514c52:	c7 85 f0 f3 ff ff 20 	mov    DWORD PTR [ebp-0xc10],0x20
  514c59:	00 00 00 
  514c5c:	ff 15 04 c2 58 00    	call   DWORD PTR ds:0x58c204
  514c62:	83 c4 10             	add    esp,0x10
  514c65:	83 c6 08             	add    esi,0x8
  514c68:	83 eb 01             	sub    ebx,0x1
  514c6b:	75 a3                	jne    0x514c10
  514c6d:	8b 9d d0 f3 ff ff    	mov    ebx,DWORD PTR [ebp-0xc30]
  514c73:	0f 28 05 e0 d8 5d 00 	movaps xmm0,XMMWORD PTR ds:0x5dd8e0
  514c7a:	8d 04 fd 07 00 00 00 	lea    eax,[edi*8+0x7]
  514c81:	03 c3                	add    eax,ebx
  514c83:	c7 85 e8 f3 ff ff 3b 	mov    DWORD PTR [ebp-0xc18],0x13b
  514c8a:	01 00 00 
  514c8d:	89 85 e4 f3 ff ff    	mov    DWORD PTR [ebp-0xc1c],eax
  514c93:	8d 85 e4 f3 ff ff    	lea    eax,[ebp-0xc1c]
  514c99:	50                   	push   eax
  514c9a:	ff 35 10 bb 5b 06    	push   DWORD PTR ds:0x65bbb10
  514ca0:	8d 85 d4 f3 ff ff    	lea    eax,[ebp-0xc2c]
  514ca6:	c7 85 ec f3 ff ff 07 	mov    DWORD PTR [ebp-0xc14],0x7
  514cad:	00 00 00 
  514cb0:	50                   	push   eax
  514cb1:	ff 35 28 20 5c 0a    	push   DWORD PTR ds:0xa5c2028
  514cb7:	0f 11 85 d4 f3 ff ff 	movups XMMWORD PTR [ebp-0xc2c],xmm0
  514cbe:	c7 85 f0 f3 ff ff 20 	mov    DWORD PTR [ebp-0xc10],0x20
  514cc5:	00 00 00 
  514cc8:	ff 15 04 c2 58 00    	call   DWORD PTR ds:0x58c204
  514cce:	6a 00                	push   0x0
  514cd0:	8d 85 f4 fb ff ff    	lea    eax,[ebp-0x40c]
  514cd6:	c7 05 3c bb 5b 06 40 	mov    DWORD PTR ds:0x65bbb3c,0x140
  514cdd:	01 00 00 
  514ce0:	8d 73 08             	lea    esi,[ebx+0x8]
  514ce3:	ba 40 01 00 00       	mov    edx,0x140
  514ce8:	6a 00                	push   0x0
  514cea:	50                   	push   eax
  514ceb:	8b ce                	mov    ecx,esi
  514ced:	e8 ae 98 ff ff       	call   0x50e5a0
  514cf2:	8d 1c fd 07 00 00 00 	lea    ebx,[edi*8+0x7]
  514cf9:	83 c4 1c             	add    esp,0x1c
  514cfc:	03 de                	add    ebx,esi
  514cfe:	89 9d d0 f3 ff ff    	mov    DWORD PTR [ebp-0xc30],ebx
  514d04:	89 1d b4 1c 5c 0a    	mov    DWORD PTR ds:0xa5c1cb4,ebx
  514d0a:	e9 65 fd ff ff       	jmp    0x514a74
  514d0f:	8b 4d f8             	mov    ecx,DWORD PTR [ebp-0x8]
  514d12:	5f                   	pop    edi
  514d13:	5e                   	pop    esi
  514d14:	33 cd                	xor    ecx,ebp
  514d16:	5b                   	pop    ebx
  514d17:	e8 92 53 07 00       	call   0x58a0ae
  514d1c:	8b e5                	mov    esp,ebp
  514d1e:	5d                   	pop    ebp
  514d1f:	c3                   	ret
