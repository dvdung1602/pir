const char UpLoad[] PROGMEM = R"=====(
    <!DOCTYPE html>
<html lang="en">
<head>
    <style>
  html,body,div,span,applet,object,iframe,h1,h2,h3,h4,h5,h6,p,blockquote,pre,a,abbr,acronym,address,big,cite,code,del,dfn,em,img,ins,kbd,q,s,samp,small,strike,strong,sub,sup,tt,var,b,u,i,center,dl,dt,dd,ol,ul,li,fieldset,form,label,legend,table,caption,tbody,tfoot,thead,tr,th,td,article,aside,canvas,details,embed,figure,figcaption,footer,header,hgroup,menu,nav,output,ruby,section,summary,time,mark,audio,video {margin: 0;padding: 0;border: 0;font-size: 100%;font: inherit;vertical-align: baseline;}
  article,aside,details,figcaption,figure,footer,header,hgroup,menu,nav,section {display: block;}
  body{line-height: 1;-moz-user-select: none !important;-webkit-touch-callout: none!important;-webkit-user-select: none!important;-khtml-user-select: none!important;-moz-user-select: none!important;-ms-user-select: none!important;}
  ol,ul {list-style: none;}blockquote,q {quotes: none;}
  blockquote:before,blockquote:after,q:before,q:after {content: '';content: none;}
  table {border-collapse: collapse;border-spacing: 0;}
      </style>
    <link rel="icon" href="https://img.lovepik.com/free-png/20220118/lovepik-download-icon-png-image_401451545_wh860.png">
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link href='https://fonts.googleapis.com/css2?family=Poppins:ital,wght@1,300&display=swap' rel='stylesheet'>
    <link rel='stylesheet' href='https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.2.1/css/all.min.css' 
    integrity='sha512-MV7K8+y+gLIBoVD59lQIYicR65iaqukzvf/nwasF0nqhPay5w/9lJmVM2hMDcnK1OnMGCdVK+iQrJ7lzPJQd1w==' 
    crossorigin='anonymous' 
    referrerpolicy='no-referrer' />
    <title>UpLoad</title>
</head>
<body>
    <script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>
  <form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>
      <input type='file' name='update' id='file' onchange='sub(this)' style=display:none>
      <label id='file-input' for='file'>   Choose file...</label>
      <input type='submit' class=btn value='Update'>
      <br><br>
      <div id='prg'></div>
      <br><div id='prgbar'><div id='bar'></div></div><br>
  </form>
<script>
    function sub(obj)
    {
        var fileName = obj.value.split('\\\\');
        document.getElementById('file-input').innerHTML = '   '+ fileName[fileName.length-1];
    };
    $('form').submit(function(e)
    {
        e.preventDefault();
        var form = $('#upload_form')[0];
        var data = new FormData(form);
        $.ajax({
        url: '/UpdatePage',
        type: 'POST',
        data: data,
        contentType: false,
        processData:false,
        xhr: function() 
        {
            var xhr = new window.XMLHttpRequest();
            xhr.upload.addEventListener('progress', function(evt) 
            {
                if (evt.lengthComputable) 
                {
                    var per = evt.loaded / evt.total;
                    $('#prg').html('progress: ' + Math.round(per*100) + '%');
                    $('#bar').css('width',Math.round(per*100) + '%');
                }
            }, false);
            return xhr;
        },
        success:function(d, s) 
        {
            console.log('success!')
        },
        error: function (a, b, c) {}
        });
    });
</script>
<style>
    input{width:12em;height:44px;border-radius:4px;margin:10px auto;font-size:20px;background:#f1f1f1;border:0;padding:0 15px}
    body{margin-bottom: 30em;background-image:url('https://1.bp.blogspot.com/-1tV9D0z38OI/VdjpxrPvDgI/AAAAAAAAC4w/NSNn4kelNoI/s1600/hinh-nen-mat-trang-trong-dem-6785.jpg');background-size: auto;font-family:sans-serif;font-size:14px;color:rgb(26, 255, 0);}
    form{background:rgba(123, 33, 165, 0.519);background-size:auto;max-width:300px;margin: 150px auto;padding:50px;border-radius:20px;text-align:center}
    .btn{background:#db4a34;width: 250px;color:#fff;cursor:pointer}
    .btn:hover{background:#4adb34;color:#fff;cursor:pointer}
    </style>
</body>
</html>
)=====";