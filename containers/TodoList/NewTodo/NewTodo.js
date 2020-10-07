import React, { Component } from 'react';
import './NewTodo.css'
import {Redirect} from "react-router-dom";
class NewTodo extends Component
{
    state = {
        title: '',
        content: '',
        submitted: false,
    }
    postTodoHandler = () => {
        const data = {title : this.state.title, content : this.state.content};
        alert(`Submitted\n${data.title}\n${data.content}`);
        this.setState({submitted: true});
    }
    render() {
        if (this.state.submitted)
        {
            return <Redirect to='/todos'/>
        }
        return (
            <div className="NewTodo">
                <h1>Add a Todo</h1>
                <label>Title</label>
                <input type="text" value={this.state.title}
                       onChange={(event) => this.setState({ title: event.target.value })} />
                <label>Content</label>
                <textarea rows="4" type="text" value={this.state.content}
                          onChange={(event) => this.setState({ content: event.target.value })} />
                <button onClick={() => this.postTodoHandler()}>Submit</button>
            </div>
        );
    }
}
export default NewTodo;