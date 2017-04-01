from flask import Flask, render_template, request, json
import subprocess
import sys  
import os

reload(sys)  
sys.setdefaultencoding('utf8')

app = Flask(__name__)



@app.route("/")
def main():
    return render_template('index.html')

@app.route('/showSignUp')
def showSignUp():
    return render_template('signup.html')

@app.route('/process',methods=['POST'])
def process():
    _input = request.form['input']
    if _input:
    	filename = "textcleaner_input"
    	if(os.path.exists(filename)):
    		os.remove(filename)


	file = open(filename,"w")
	file.write(_input)
	file.close()
	output = subprocess.Popen(["./a.out"], stdout=subprocess.PIPE).communicate()[0]
	print output
    return render_template('result.html', res=output)



if __name__ == "__main__":
    app.run(host='0.0.0.0')
