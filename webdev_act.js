const {createClient} = supabase

const supabase_url = "https://wwdaochdkrdaumjuwdxc.supabase.co"
const supabase_key = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6Ind3ZGFvY2hka3JkYXVtanV3ZHhjIiwicm9sZSI6ImFub24iLCJpYXQiOjE3MTIxMTM2ODgsImV4cCI6MjAyNzY4OTY4OH0.jmeSsVO6kG3F5Uthc4JfjzCxpjHXAzzZyvW-3J9cMLo"

const connection = createClient(supabase_url, supabase_key) 



async function read(){
    let {data,error} = await connection.from('faculty_table').select().neq('is_deleted',1)
    for (let i = 0; i < data.length; ++i){
        let list = document.querySelector('.return_list')
        let list_item = document.createElement("li");
        let button_item = document.createElement("button");
        button_item.textContent = "delete";
        button_item.onclick = function() {softdeleteData(data[i].id)}
        list_item.textContent = data[i].name;
        list_item.appendChild(button_item);
      
        list.appendChild(list_item);
    }
    console.log("read")
}

async function deleteData(i){

    let {data,error} = await connection.from('faculty_table').delete().eq('id',i);
    let list = document.querySelector('.return_list')
    while (list.length > 0) {
        list.pop();
      }
    // data.update({'department':department.value}).eq('id',id.textContent);
    read();
}   

async function softdeleteData(i){
    
    let {data,error} = await connection.from('faculty_table').update({'is_deleted':1}).eq('id',i);
    let list = document.querySelector('.return_list')
    while (list.firstChild) {
        list.removeChild(list.firstChild);
        }
    // data.update({'department':department.value}).eq('id',id.textContent);
    read();
    console.log("Deleted");
    // data.update({'age':age.value}).eq('id',id.textContent);
    // data.update({'department':department.value}).eq('id',id.textContent);
}   

async function refresh(){
    
    
    let {data,error} = await connection.from('faculty_table').update({'is_deleted':0}).eq('is_deleted',1);
    
    console.log("refreshed");
}


