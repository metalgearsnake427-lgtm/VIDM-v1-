use ffmpeg_next as ffmpeg;
use std::os::raw::c_char;
use std::ffi::{CString, CStr};
use reqwest;
use tokio;

#[no_mangle]
pub extern "C" fn get_ffmpeg_version() -> *const c_char {
    let version = ffmpeg::util::version();
    let s = CString::new(version.to_string()).unwrap();
    s.into_raw()
}

/
async fn perform_search(query: &str) -> Result<String, reqwest::Error> {
    let url = format!("https://api.example.com/search?q={}", query);
    let response = reqwest::get(url).await?;
    let body = response.text().await?;
    Ok(body)
}

#[no_mangle]
pub extern "C" fn run_rust_internet_search(c_query: *const c_char) {
    let query_str = unsafe {
        if c_query.is_null() { 
            return; // Early return if the query is null
        } else {
            match CStr::from_ptr(c_query).to_str() {
                Ok(s) => s,
                Err(_) => return, // Handle invalid UTF-8
            }
        }
    };

    // Using a block_on or a dedicated runtime for the FFI boundary
    let rt = tokio::runtime::Runtime::new().unwrap();
    match rt.block_on(perform_search(query_str)) {
        Ok(result) => println!("[Rust] Universal Search Success for: {}\nResult: {}", query_str, result),
        Err(e) => eprintln!("[Rust] Search Error: {}", e),
    }
}

};
