ARG BASE_IMAGE
ARG BASE_VERSION

FROM ${BASE_IMAGE}:${BASE_VERSION} AS development
ARG DEVEL_DEPS

# Install development dependencies
RUN apt-get update
RUN apt-get install -y ${DEVEL_DEPS}
RUN apt-get autoremove -y
RUN apt-get autoclean -y

# Create a non-root user
ARG USER_ID
ARG USER_NAME
ARG USER_SHELL
RUN useradd --create-home --shell ${USER_SHELL} --uid ${USER_ID} --user-group ${USER_NAME}
RUN echo "${USER_NAME} ALL=(ALL:ALL) NOPASSWD:ALL" >> /etc/sudoers.d/${USER_NAME}
RUN install --directory --owner=${USER_NAME} --group=${USER_NAME} /home/${USER_NAME}/.ssh

# Switch to the non-root user
USER ${USER_NAME}
WORKDIR /home/${USER_NAME}

# Install Rust toolchain
RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- --component clippy,rustfmt -y
ENV PATH="/home/${USER_NAME}/.cargo/bin:${PATH}"
