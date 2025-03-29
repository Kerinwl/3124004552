<template>
  <div class="auth-container">
    <div class="auth-card">
      <!-- 标题 -->
      <h1 class="title">用户系统</h1>
      
      <!-- 切换按钮 -->
      <div class="tabs">
        <button
          :class="{ active: isLogin }"
          @click="switchToLogin"
        >
          登录
        </button>
        <button
          :class="{ active: !isLogin }"
          @click="switchToRegister"
        >
          注册
        </button>
      </div>

      <!-- 登录表单 -->
      <form v-if="isLogin" @submit.prevent="handleLogin" class="auth-form">
        <div class="form-group">
          <input
            v-model="loginForm.email"
            type="text"
            placeholder="邮箱/手机号"
            required
          >
        </div>
        <div class="form-group">
          <input
            v-model="loginForm.password"
            type="password"
            placeholder="密码"
            required
            minlength="6"
          >
        </div>
        <button type="submit" class="submit-btn">登录</button>
      </form>

      <!-- 注册表单 -->
      <form v-else @submit.prevent="handleRegister" class="auth-form">
        <div class="form-group">
          <input
            v-model="registerForm.email"
            type="email"
            placeholder="邮箱"
            required
          >
        </div>
        <div class="form-group">
          <input
            v-model="registerForm.phone"
            type="tel"
            placeholder="手机号"
            required
            pattern="[0-9]{11}"
          >
        </div>
        <div class="form-group">
          <input
            v-model="registerForm.password"
            type="password"
            placeholder="密码"
            required
            minlength="6"
          >
        </div>
        <div class="form-group">
          <input
            v-model="registerForm.confirmPassword"
            type="password"
            placeholder="确认密码"
            required
            :class="{ error: !passwordMatch }"
          >
          <span v-if="!passwordMatch" class="error-msg">两次密码不一致</span>
        </div>
        <button 
          type="submit" 
          class="submit-btn"
          :disabled="!passwordMatch"
        >
          注册
        </button>
      </form>
    </div>
  </div>
</template>

<script>
export default {
  name: 'AuthPage',
  data() {
    return {
      isLogin: true,
      loginForm: {
        email: '',
        password: ''
      },
      registerForm: {
        email: '',
        phone: '',
        password: '',
        confirmPassword: ''
      }
    }
  },
  computed: {
    passwordMatch() {
      return this.registerForm.password === this.registerForm.confirmPassword && 
             this.registerForm.password !== ''
    }
  },
  methods: {
    switchToLogin() {
      this.isLogin = true
    },
    switchToRegister() {
      this.isLogin = false
    },
    handleLogin() {
      alert(`模拟登录成功\n邮箱: ${this.loginForm.email}`)
    },
    handleRegister() {
      if (this.passwordMatch) {
        alert(`模拟注册成功\n邮箱: ${this.registerForm.email}\n手机号: ${this.registerForm.phone}`)
      }
    }
  }
}
</script>

