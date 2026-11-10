; Original Windows 3.89.1 native file, PE image base 00400000.
; Static wait frames, unique quest-list caller and empty-list branch.
; D3BF0 entry recovered with objdump starting exactly at the native CALL target.
  4d3bf0:	55                   	push   ebp
  4d3bf1:	8b ec                	mov    ebp,esp
  4d3bf3:	83 e4 f8             	and    esp,0xfffffff8
  4d3bf6:	83 ec 10             	sub    esp,0x10
  4d3bf9:	8d 14 24             	lea    edx,[esp]
  4d3bfc:	e8 ff df ff ff       	call   0x4d1c00
  4d3c01:	83 f8 9d             	cmp    eax,0xffffff9d
  4d3c04:	75 09                	jne    0x4d3c0f
  4d3c06:	e8 15 eb ff ff       	call   0x4d2720
  4d3c0b:	8b e5                	mov    esp,ebp
  4d3c0d:	5d                   	pop    ebp
  4d3c0e:	c3                   	ret
  4d3c0f:	83 f8 fe             	cmp    eax,0xfffffffe
  4d3c12:	75 04                	jne    0x4d3c18
  4d3c14:	8b e5                	mov    esp,ebp
  4d3c16:	5d                   	pop    ebp
  4d3c17:	c3                   	ret
  4d3c18:	83 f8 d6             	cmp    eax,0xffffffd6
  4d3c1b:	75 04                	jne    0x4d3c21
  4d3c1d:	8b e5                	mov    esp,ebp
  4d3c1f:	5d                   	pop    ebp
  4d3c20:	c3                   	ret
  4d3c80:	55                   	push   ebp
  4d3c81:	8b ec                	mov    ebp,esp
  4d3c83:	83 ec 3c             	sub    esp,0x3c
  4d3c86:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  4d3c8b:	33 c5                	xor    eax,ebp
  4d3c8d:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  4d3c90:	83 3d 5c ba 5b 06 00 	cmp    DWORD PTR ds:0x65bba5c,0x0
  4d3c97:	56                   	push   esi
  4d3d05:	e8 e6 fe ff ff       	call   0x4d3bf0
  4d3d0a:	83 f8 01             	cmp    eax,0x1
  4d3d0d:	7c f6                	jl     0x4d3d05
  4d3d0f:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  4d3d12:	33 cd                	xor    ecx,ebp
  4d3d14:	5e                   	pop    esi
  4d3d15:	e8 94 63 0b 00       	call   0x58a0ae
  4d3d1a:	8b e5                	mov    esp,ebp
  4d3d1c:	5d                   	pop    ebp
  4d3d1d:	c3                   	ret
  558ce0:	55                   	push   ebp
  558ce1:	8b ec                	mov    ebp,esp
  558ce3:	81 ec 2c 04 00 00    	sub    esp,0x42c
  558ce9:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  558cee:	33 c5                	xor    eax,ebp
  558cf0:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  558cf3:	0f 28 05 c0 da 5d 00 	movaps xmm0,XMMWORD PTR ds:0x5ddac0
  558d99:	e8 b2 a7 fb ff       	call   0x513550
  558d9e:	b9 16 c6 58 00       	mov    ecx,0x58c616
  558da3:	e8 f8 f9 ff ff       	call   0x5587a0
  558da8:	8b 1d f4 0e 62 0a    	mov    ebx,DWORD PTR ds:0xa620ef4
  558dae:	89 85 d4 fb ff ff    	mov    DWORD PTR [ebp-0x42c],eax
  558db4:	89 1d bc 1c 5c 0a    	mov    DWORD PTR ds:0xa5c1cbc,ebx
  558dba:	c7 05 10 20 5c 0a 10 	mov    DWORD PTR ds:0xa5c2010,0x10
  558dc1:	00 00 00 
  558dc4:	85 c0                	test   eax,eax
  558dc6:	0f 84 84 04 00 00    	je     0x559250
  55931c:	c7 05 5c ba 5b 06 01 	mov    DWORD PTR ds:0x65bba5c,0x1
  559323:	00 00 00 
  559326:	c7 05 34 56 35 06 01 	mov    DWORD PTR ds:0x6355634,0x1
  55932d:	00 00 00 
  559330:	e8 4b a9 f7 ff       	call   0x4d3c80
  559335:	c7 05 5c ba 5b 06 00 	mov    DWORD PTR ds:0x65bba5c,0x0
  55933c:	00 00 00 
  57ded9:	e8 02 ae fd ff       	call   0x558ce0
  57dede:	e9 b3 01 00 00       	jmp    0x57e096
