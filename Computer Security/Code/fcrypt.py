import sys
from Crypto.Cipher import PKCS1_OAEP
from Crypto.PublicKey import RSA
from Crypto.Cipher import AES
from os import urandom


if (sys.argv[1] == "--encrypt"):
  f = open(sys.argv[3], 'rb')
  message = f.read()
  f.close()
  randomKey = urandom(16)
  cipher = AES.new(randomKey, AES.MODE_GCM)
  cipherText, tag = cipher.encrypt_and_digest(message)
  nonce = cipher.nonce

  privateKey = RSA.generate(2048)
  f = open('privateKey.pem', 'wb')
  f.write(privateKey.export_key('PEM'))
  f.close()

  publicKey = privateKey.public_key()
  f = open('publicKey.pem', 'wb')
  f.write(publicKey.export_key('PEM'))
  f.close()
  
  keyCipher = PKCS1_OAEP.new(publicKey)
  cipherKey = keyCipher.encrypt(randomKey)

  f = open(sys.argv[4], "wb")
  f.truncate(0)
  f.write(cipherKey)
  f.write(tag)
  f.write(nonce)
  f.write(cipherText)
  f.close()

  print("Encryption Successful.")

elif (sys.argv[1] == "--decrypt"):
  privateKey = RSA.importKey(open(sys.argv[2]).read())
  
  f = open(sys.argv[3], 'rb')
  cipherKey = f.read(256)
  tag = f.read(16)
  nonce = f.read(16)
  cipherText = f.read()
  f.close()

  cipher = PKCS1_OAEP.new(privateKey)
  key = cipher.decrypt(cipherKey)
  decrypt = AES.new(key, AES.MODE_GCM, nonce=nonce)
  message = decrypt.decrypt_and_verify(cipherText, tag)

  f = open(sys.argv[4], "wb")
  f.truncate(0)
  f.write(message)
  f.close

  print("Decryption Successful.")