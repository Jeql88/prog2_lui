const {createClient} = supabase

const supabase_url = "https://wwdaochdkrdaumjuwdxc.supabase.co"
const supabase_key = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6Ind3ZGFvY2hka3JkYXVtanV3ZHhjIiwicm9sZSI6ImFub24iLCJpYXQiOjE3MTIxMTM2ODgsImV4cCI6MjAyNzY4OTY4OH0.jmeSsVO6kG3F5Uthc4JfjzCxpjHXAzzZyvW-3J9cMLo"

const connection = createClient(supabase_url, supabase_key) 

async function read(){
    let {data,error} = await connection.from('faculty_table').select()
    for (let i = 0; i < data.length; ++i){
        const list = document.querySelector('.return_list')
        let list_item = document.createElement("li");
        let button_item = document.createElement("button");
        button_item.textContent = "select";
        button_item.onclick = function() {select(i)}
        list_item.textContent = data[i].name;
        list_item.appendChild(button_item);
        list.appendChild(list_item);
    }
    console.log(data)
}

async function select(i){
    let name = document.querySelector('#Name');
    let age = document.querySelector('#Age');
    let department = document.querySelector('#Department');
    let id = document.querySelector('#id');
    
    let {data,error} = await connection.from('faculty_table').select()
    id.textContent = data[i].id;
    name.value = data[i].name;
    age.value = data[i].age;
    department.value = data[i].department

    
}
async function update(){
    let name = document.querySelector('#Name');
    let age = document.querySelector('#Age');
    let department = document.querySelector('#Department');
    let id = document.querySelector('#id');
    const {data,error} = await connection.from('faculty_table').update({'name':name.value,'age':age.value,'department':department.value}).eq('id',id.textContent);
    console.log(error)
    // data.update({'age':age.value}).eq('id',id.textContent);
    // data.update({'department':department.value}).eq('id',id.textContent);
    
}

