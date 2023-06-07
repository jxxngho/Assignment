const express=require('express')
const fs=require('fs')
const app=express()
const bodyParser=require('body-parser')
const { request } = require('http')
const { response } = require('express')

app.use(bodyParser.urlencoded({extended : false}))
let errStack=0 // 비밀번호 틀린 횟수
let  count_id=0 // 아이디 오류시 사용할 변수 

//서버 접속하면 로그인 화면 전송받음
app.get("/", (request,response)=>{
    fs.readFile("C:/Users/admin/Desktop/JSCRIPT/final/login.html",(error,data)=>{
        response.writeHead(200,{'Content-Type':"text/html"})
        response.end(data)
    })
});

//회원가입페이지
app.get("/sign", (request,response)=>{
    fs.readFile("C:/Users/admin/Desktop/JSCRIPT/final/sign.html",(error,data)=>{
        response.writeHead(200,{'Content-Type':"text/html"})
        response.end(data)
    })
});
//객체 만드는 용도
class tmp{
    constructor(id,pwd){
        this.id=id
        this.pwd=pwd
    }
}

let stream=fs.createWriteStream("C:/Users/admin/Desktop/JSCRIPT/final/id.txt",{flags:'a'})

// 회원가입 성공시
// 긱 아이다마다 파일 하나를 만들어줌.
app.get("/save",(request,response)=>{
    let id=request.query.user_id
    let pw=request.query.user_pw
    let arr=new tmp(id,pw)
    fs.writeFileSync(`${id}.txt`,'')
    stream.write("\n"+JSON.stringify(arr))

    let subject = fs.readFileSync('subject.txt','utf-8').toString()
    let enroll = fs.readFileSync('enroll.txt','utf-8').toString()
    fs.writeFileSync(`${id}_subject.txt`,subject,'utf-8')
    fs.writeFileSync(`${id}_enroll.txt`,enroll,'utf-8')
    // 만든 후 로그인 화면으로 이동
    response.redirect("http://localhost:52273")
})

//로그인시도
app.get("/confirm", (request,response)=>{
    let id=request.query.user_id // 로그인 시도한 아이디
    let pw=request.query.user_pw // 로그인 시도한 비밀번호
    let readData2=fs.readFileSync("C:/Users/admin/Desktop/JSCRIPT/final/id.txt")
    let data2=[]
    data2=readData2.toString().split('\n')
    let result2=[]

    for(i of data2){
        result2.push(JSON.parse(i)) //json으로
    }
    for(i in result2){
        if(id==result2[i].id){
            if(pw==result2[i].pwd){
                count_id=0
                //로그인성공
                if(id=="admin"){ //관리자일 경우
                    response.writeHead(200,{'Content-Type':'text/html; charset=utf-8'});
                    response.write("<script>window.location='/admin'</script>")
                    break;
                
                }
                success_id=id
                response.writeHead(200,{'Content-Type':'text/html; charset=utf-8'});
                response.write("<script>window.location='/success'</script>")
                // "다음" 화면으로 이동
                break;                
            }
            else{
                count_id=0
                errStack++;
                if(errStack==3){ // 비밀번호 3번 틀릴시
                    errStack=0;
                    fs.readFile("C:/Users/admin/Desktop/JSCRIPT/final/password_3err.html",(error,data)=>{
                        response.writeHead(200,{'Content-Type':"text/html"})
                        response.end(data)
                    })
                }
                else{   //비밀번호 에러
                    fs.readFile("C:/Users/admin/Desktop/JSCRIPT/final/password.err.html",(error,data)=>{
                        response.writeHead(200,{'Content-Type':"text/html"})
                        response.end(data)
                    })
                }
                break;
            }
        }
        count_id++;
    }

    if(count_id==result2.length){   //아이디 오류시
        count_id=0
        fs.readFile("C:/Users/admin/Desktop/JSCRIPT/final/id_err.html",(error,data)=>{
        response.writeHead(200,{'Content-Type':"text/html"})
        response.end(data)
    })
    }
    count=0      

});

// "다음 화면 "
app.get("/success",(request,response)=>{
    let sum=0 // 총 수강 신청한 학점 총점
    // subject_id에 맞는 파일을 들고온다. 
    
    let subject= fs.readFileSync(`${success_id}_subject.txt`,'utf-8').toString()
    subject = JSON.parse(subject);
    let enroll = fs.readFileSync(`${success_id}_enroll.txt`,'utf-8').toString()
    enroll = JSON.parse(enroll);  
   
    let application='<h2>신청가능한 교과목</h2>'
    for(var i=0;i<subject.class.length;i++){
        application+=`${subject.class[i]} - ${subject.credit[i]}학점<br>`
    }
    application+='<hr>'

    let ed='<h2>신청한 교과목 </h2>'
    for(var i=0;i<enroll.class.length;i++){
        ed+=`${enroll.class[i]} - ${enroll.credit[i]}학점<br>`
    }
     ed+='<hr>'
    for(let i=0; i<enroll.credit.length; i++){
        sum+=enroll.credit[i]
    }

    //화면에 출력

    let success = fs.readFileSync('C:/Users/admin/Desktop/JSCRIPT/final/success.html','utf-8').toString()
    response.writeHead(200,{'Content-Type':'text/html; utf-8'})
    response.write(success)
    response.write(application)
    response.write(ed)
    response.write(`수강신청한 학점 : ${sum}`)
    response.end()
    
    //버튼작동
    app.post('/add_delete',(request,response)=>{
        let button=request.body.butt
        if(button=="add"){ //추가
            if(subject.class.includes(request.body.subject)==true){
                let index=subject.class.indexOf(request.body.subject)
                
                enroll.class.push(request.body.subject)
                sum+=subject.class
                enroll.credit.push(subject.credit[index])
                subject.class.splice(index,1)
                subject.credit.splice(index,1)
        
                fs.writeFileSync(`${success_id}_subject.txt`,JSON.stringify(subject),'utf-8')
                fs.writeFileSync(`${success_id}_enroll.txt`,JSON.stringify(enroll),'utf-8')
                // response.write("<script> alert('추가되었습니다.') </script>")
                response.send("<script>window.location='/success'</script>")
            }
            //교과목 이름을 잘못쳐서 교과목이 없는 경우
            else{    
                response.writeHead(200,{'Content-Type':'text/html; charset=utf-8'});
                response.write(`<script>alert('${request.body.subject}이란 과목은 없습니다. 다시 입력바랍니다')</script>`)
                response.write("<script>window.location='/success'</script>")
                // console.log("else1문 체크")
            }
        }
        // 삭제할 경우 delete // add반대로 코드
        else{ 
            // console.log("check point1")       
            if(enroll.class.includes(request.body.subject)==true){
                let index=enroll.class.indexOf(request.body.subject)
                
                subject.class.push(request.body.subject)
                sum-=subject.class
                subject.credit.push(enroll.credit[index])
                enroll.class.splice(index,1)
                enroll.credit.splice(index,1)
        
                fs.writeFileSync(`${success_id}_subject.txt`,JSON.stringify(subject),'utf-8')
                fs.writeFileSync(`${success_id}_enroll.txt`,JSON.stringify(enroll),'utf-8')
                // response.write("<script> alert('추가되었습니다.') </script>")
                response.send("<script>window.location='/success'</script>")
            }
            //교과목 이름을 잘못쳐서 교과목이 없는 경우
            else{    
                response.writeHead(200,{'Content-Type':'text/html; charset=utf-8'});
                response.write(`<script>alert('${request.body.subject}이란 과목은 없습니다. 다시 입력바랍니다')</script>`)
                response.write("<script>window.location='/success'</script>")
                // console.log("else1문 체크")
            }

        }
    })
    
})
// 관리자모드
app.get("/admin",(request,response)=>{
    response.write("<h1>관리자모드</h1>")
})



//서버 실행
app.listen(52273,()=>{
    console.log('Server start')
})