package main

import (
	"log"
	"net/http"
)

func guildMux(w http.ResponseWriter, r *http.Request) {
	if r.Method != "GET" {
		return
	}
}

func main() {
	mux := http.NewServeMux()
	mux.HandleFunc("/", guildMux)
	log.Print("starting server on :3472")
	err := http.ListenAndServe(":3472", mux)
	log.Fatal(err)
}
