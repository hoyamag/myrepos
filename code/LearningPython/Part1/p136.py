exec(open('script1.py').read())
# exec(open.('filename').read()) is better way to run file than import and reload in interactive shell

# be careful to overwrite a name
x = 10
print('x =', x)
exec(open('script1.py').read())# x is overwritten by exec call
print('x =', x)

