# 为了简化并更好地标示异步IO,从Python3.5开始引入了新的语法async和await

import asyncio

async def hello():
	print("Hello, Wrold!")
	r = await asyncio.sleep(1)
	print("Hello again!")

loop = asyncio.get_event_loop()
tasks = [hello(), hello()]
loop.run_until_complete(asyncio.wait(tasks))
loop.close()