print('first import script1');
import script1
print('import again(must be unprinted')
import script1
print('reload script1')
import imp
imp.reload(script1)
print('reload again script1(internally, it''s called by reload loaded by from') 
from imp import reload
reload(script1)
