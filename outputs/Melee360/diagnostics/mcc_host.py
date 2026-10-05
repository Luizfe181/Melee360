"""Explicit opt-in TCP host for original MCC's adapter memory/mailbox protocol.
No FIO filesystem access. One 128 KiB adapter per connection, big-endian wire.
"""
import argparse,socket,struct,json,time
MAGIC=0x4d334849
class Adapter:
 def __init__(self):
  self.memory=bytearray(0x20000);self.memory[0x600:0x620]=b'HUDSON/USB2EXI/INITCODE/HOST'.ljust(32,b'\0');self.mail=[];self.operations=0
 def transact(self,op,address,size,value,payload):
  self.operations+=1;data=b'';ok=1
  if op in (1,2):
   if address>len(self.memory) or size>len(self.memory)-address:ok=0
   elif op==1:data=bytes(self.memory[address:address+size])
   else:
    self.memory[address:address+size]=payload
    if address==0x700 and size==64:
     for channel in range(1,16):
      at=0x700+channel*4;connection=self.memory[at+2]
      if connection==2:self.memory[at+2]=3;self.mail.append((channel<<24)|1)
      elif connection==1:self.memory[at:at+4]=b'\0'*4
     self.mail.append(5)
  elif op==3:
   channel=(value>>24)&15;event=value&0xffffff
   if channel==0 and event==1:self.memory[0x600:0x620]=b'HUDSON/USB2EXI/INITCODE/HOST'.ljust(32,b'\0')
   elif channel==0 and event==3:self.mail.append(4)
   elif value&0x10000000:self.mail.append(value) # debug host echoes notifications
  elif op not in (0,4):ok=0
  messages=self.mail;self.mail=[]
  return struct.pack('!4I',MAGIC,ok,len(messages),len(data))+b''.join(struct.pack('!I',m) for m in messages)+data

def exact(connection,size):
 result=b''
 while len(result)<size:
  data=connection.recv(size-len(result))
  if not data:raise EOFError
  result+=data
 return result

def serve(bind,port,report):
 with socket.socket() as listener:
  listener.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1);listener.bind((bind,port));listener.listen(1)
  print(f'MCC host ready {bind}:{listener.getsockname()[1]}',flush=True)
  while True:
   connection,address=listener.accept();adapter=Adapter()
   with connection:
    try:
     while True:
      magic,op,offset,size,value=struct.unpack('!5I',exact(connection,20))
      if magic!=MAGIC or size>0x20000:raise ValueError('invalid bounded request')
      payload=exact(connection,size) if op==2 else b''
      connection.sendall(adapter.transact(op,offset,size,value,payload))
    except (EOFError,ConnectionError,OSError,ValueError):pass
   if report:
    with open(report,'w') as f:json.dump({'peer':address,'operations':adapter.operations},f)
if __name__=='__main__':
 parser=argparse.ArgumentParser();parser.add_argument('--bind',default='127.0.0.1');parser.add_argument('--port',type=int,default=36729);parser.add_argument('--report');args=parser.parse_args();serve(args.bind,args.port,args.report)
